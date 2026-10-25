#
#  Makefile for CPU-R project
#
#  (c) 2026 TDolphin
#

#
# note: for cross compilation requires 'jlha-utils' under linux
#

SUB_PROJECTS = app
APP_DRAWER_NAME = CPU-R

OUT_PATH = out
OUT_APP_PATH = $(OUT_PATH)/$(APP_DRAWER_NAME)

include app/appversion.txt

help: all

all:
	@echo "make cross_aros_x86_64 - AROS x86_64 build (cross compilation on linux)"
	@echo "make clean.obj - remove all obj files"
	@echo "make clean - remove all obj files and executable files"

cross_aros_x86_64: sub_projects_cross_aros_x86_64 build_out

sub_projects_build:
	@echo "------------------------------------------------"
	@date
	@for dir in $(SUB_PROJECTS); do \
		$(MAKE) $(BUILD_TARGET) -C $$dir; \
	done
	@date
	@echo "------------------------------------------------"

sub_projects_cross_aros_x86_64: BUILD_TARGET=cross_aros_x86_64
sub_projects_cross_aros_x86_64: sub_projects_build

build_out:
	mkdir -p $(OUT_APP_PATH)
	@for dir in $(SUB_PROJECTS); do \
		echo "copy ... " $$dir/out/aros/x86_64/"*" $(OUT_APP_PATH); \
		cp -R $$dir/out/aros/x86_64/* $(OUT_APP_PATH); \
	done
	mkdir -p $(OUT_APP_PATH)/images
	cp -r data/images/* $(OUT_APP_PATH)/images
	mkdir -p $(OUT_APP_PATH)/specs
	cp -r data/specs/*.csv $(OUT_APP_PATH)/specs
	cp docs/header.readme $(OUT_APP_PATH)/CPU-R.readme
	sed -i "s/%VERSION%/$(APP_VERSION)/g" $(OUT_APP_PATH)/CPU-R.readme
	fold -w78 -s docs/CPU-R.readme >> $(OUT_APP_PATH)/CPU-R.readme
	cp data/icons/CPU-R.drawer.info $(OUT_PATH)/CPU-R.info
	cp data/icons/CPU-R.info $(OUT_APP_PATH)
	cp data/icons/CPU-R.readme.info $(OUT_APP_PATH)
	cp LICENSE $(OUT_APP_PATH)
	cp data/icons/LICENSE.info $(OUT_APP_PATH)
	rm -f $(OUT_APP_PATH)/$(APP_DRAWER_NAME)_*
	cd $(OUT_PATH); lha a $(APP_DRAWER_NAME).lha $(APP_DRAWER_NAME) $(APP_DRAWER_NAME).info

clean.obj:
	@for dir in $(SUB_PROJECTS); do \
		$(MAKE) clean.obj -C $$dir; \
	done

clean: clean.obj
	rm -f -R $(OUT_PATH)/*
	@for dir in $(SUB_PROJECTS); do \
		$(MAKE) clean -C $$dir; \
	done

rebuild_cross_aros_x86_64: clean cross_aros_x86_64 build_out

AOSCPP_PATH ?= ../AmigaOS.cpp.wrapper
MUICPP_PATH ?= ../AmigaOS.MUI.cpp.wrapper

check:
	cppcheck --enable=all --inconclusive \
		--suppress=missingInclude --suppress=missingIncludeSystem \
		--suppress=*:$(AOSCPP_PATH)/wrappers/* \
		--suppress=*:$(MUICPP_PATH)/* \
		--suppress=*:/gg/os-include/* \
		--suppress=unusedFunction:app/src/AppContext.cpp \
		--suppress=functionStatic:app/src/AppContext.hpp \
		--suppress=useStlAlgorithm:app/src/Components/Tabs/OSTab.cpp \
		-I app/src \
		-I $(AOSCPP_PATH)/wrappers/src \
		-I $(MUICPP_PATH)/wrappers/src \
		-I $(MUICPP_PATH)/components/src \
		-I /gg/os-include \
		-D__AROS__ \
		app/src

.NOTPARALLEL: build_out