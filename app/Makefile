#
#  MakeFile for CPU-R
#
#  (c) 2026 TDolphin
#

include appversion.txt

export APP_DATE = `date +%d.%m.%Y`
export APP_FILE_NAME = CPU-R
export APP_BUILD_COMMIT_HASH = `git rev-parse HEAD`

dir_guard = mkdir -p $@

all:
	@echo "make cross_aros_x86_64"

cross_aros_x86_64: TARGET="cross AROS x86_64"
cross_aros_x86_64: CPPC=x86_64-aros-g++
cross_aros_x86_64: CC=x86_64-aros-gcc
cross_aros_x86_64: STRIP=x86_64-aros-strip
cross_aros_x86_64: OBJDUMP=x86_64-aros-objdump
cross_aros_x86_64: build

# AROS "Development" tree (sysroot with Zune headers/libs). Machine-independent
# path: on machines that follow the convention it is /opt/aros/Development.
# Override per-build with:
#   make cross_aros_x86_64 AROS_SYSROOT=/custom/path
AROS_SYSROOT ?= /opt/aros/Development

build: out/aros/x86_64
	@echo "# Build for $(TARGET) ..."
	$(MAKE) -f makefile.generic.gcc.mk SUB_BUILD_PATH=aros/x86_64 \
	AOSCPP_PATH=../../AmigaOS.cpp.wrapper \
	MUICPP_PATH=../../AmigaOS.MUI.cpp.wrapper \
	CPPC=$(CPPC) CC=$(CC) STRIP=$(STRIP) OBJDUMP=$(OBJDUMP) \
	MORE_CPP_FLAGS="-std=gnu++17 --sysroot=$(AROS_SYSROOT)" \
	MORE_LFLAGS="" \
	all

out/aros/x86_64:
	$(dir_guard)

clean.obj:
	rm -f -R ../../AmigaOS.cpp.wrapper/wrappers/obj/*
	rm -f -R ../../AmigaOS.MUI.cpp.wrapper/components/obj/*
	rm -f -R obj/*

clean: clean.obj
	rm -f -R out/*

rebuild : clean all
