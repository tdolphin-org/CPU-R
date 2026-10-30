#
#  CPU-R
#
#  (c) 2026 TDolphin
#
#  generic makefile for gcc
#
#  AROS x86_64 cross compilation (hosted, Linux):
#    setup from -> https://elwis.github.io/aros-getting-started/docs/01-build-environment.html
#    requires: AROS stable (ABIv11) sources (https://github.com/deadwood2/AROS),
#              cross-compiler built via scripts/rebuild.sh (x86_64-aros-g++),
#              Zune (MUI 3.x-compatible) headers are part of the AROS SDK
#

# trace/debug flags
DEBUG_FLAGS = #-DTRACE -DTRACE_CUSTOM_COMPONENTS -DTRACE_AMIGAOS

CPP_FLAGS = $(DEBUG_FLAGS) $(MORE_CPP_FLAGS) -D_NO_PPCINLINE -Wall -D_GLIBCXX_USE_WCHAR_T=0\
	-Isrc -I${AOSCPP_PATH}/wrappers/src -I${MUICPP_PATH}/wrappers/src -I${MUICPP_PATH}/components/src \
	-fno-rtti -ffunction-sections -fdata-sections\
	-Os -flto
LFLAGS = -L${AOSCPP_PATH}/wrappers/lib/$(SUB_BUILD_PATH) -L${MUICPP_PATH}/wrappers/lib/$(SUB_BUILD_PATH) -lamiga_std_light -lMUIcpp\
	$(MORE_LFLAGS) -flto

dir_guard = mkdir -p $(@D)

BINPATH = out/$(SUB_BUILD_PATH)

include makefile.gen.version.mk

AOS_WRAPPER_PATH = ${AOSCPP_PATH}/wrappers
AOS_WRAPPER_MODULES = Core \
	AOS/Exec AOS/AmigaLib AOS/OpenURL AOS/Graphics AOS/Cybergraphics AOS/Dos AOS/Icon \
	AOS/Intuition AOS/ASL
AOS_WRAPPER_SRC_DIRS = $(addprefix $(AOS_WRAPPER_PATH)/src/,$(AOS_WRAPPER_MODULES))
AOS_WRAPPER_SRCS = $(foreach sdir,$(AOS_WRAPPER_SRC_DIRS),$(wildcard $(sdir)/*.cpp))
AOS_WRAPPER_CPP_FLAGS = $(CPP_FLAGS) -fno-threadsafe-statics

MUI_COMPONENTS_PATH = ${MUICPP_PATH}/components
MUI_COMPONENTS_MODULES = Components/Core Components/MCC Components/MCC/Core Components/Buttons Components/Tabs
MUI_COMPONENTS_SRC_DIRS = $(addprefix $(MUI_COMPONENTS_PATH)/src/,$(MUI_COMPONENTS_MODULES))
MUI_COMPONENTS_SRCS = $(foreach sdir,$(MUI_COMPONENTS_SRC_DIRS),$(wildcard $(sdir)/*.cpp))

MODULES_COMPONENTS = Components Components/Buttons Components/Core Components/Tabs Components/Tabs/CPU Components/Tabs/Memory Components/Tabs/Expansions \
	Components/Tabs/Graphics Components/Tabs/Boards Components/Windows Components/Menus
MODULES = $(MODULES_COMPONENTS) FileResources TextResources DataInfo

SRC_DIRS = src $(addprefix src/,$(MODULES))
SRCS = $(foreach sdir,$(SRC_DIRS),$(wildcard $(sdir)/*.cpp))
ASM_SRCS = $(foreach sdir,$(SRC_DIRS),$(wildcard $(sdir)/*.s))
OBJS = $(patsubst src/%.cpp,obj/$(SUB_BUILD_PATH)/%.o,$(SRCS))\
	$(patsubst src/%.s,obj/$(SUB_BUILD_PATH)/%.o,$(ASM_SRCS))\
	$(patsubst $(AOS_WRAPPER_PATH)/src/%.cpp,$(AOS_WRAPPER_PATH)/obj/$(SUB_BUILD_PATH)/%.o,$(AOS_WRAPPER_SRCS))\
	$(patsubst $(MUI_COMPONENTS_PATH)/src/%.cpp,$(MUI_COMPONENTS_PATH)/obj/$(SUB_BUILD_PATH)/%.o,$(MUI_COMPONENTS_SRCS))

HEADERS = src/ProgDefines.hpp

all: src/Version.cpp src/Version.hpp $(BINPATH)/$(APP_FILE_NAME)

$(BINPATH)/$(APP_FILE_NAME): $(OBJS)
	@echo "## Linking ..."
	$(CPPC) $^ $(LFLAGS) -o $@_nonstripped
	@echo "## Stripping ..."
	$(STRIP) --strip-all --strip-unneeded $@_nonstripped -o $@
	$(OBJDUMP) --syms --reloc --disassemble-all $@_nonstripped > $@_disassembled
	@echo "## Finished :)"

obj/$(SUB_BUILD_PATH)/%.o: src/%.cpp src/%.hpp $(HEADERS)
	$(dir_guard)
	$(CPPC) $(CPP_FLAGS) -c $< -o $@

obj/$(SUB_BUILD_PATH)/%.o: src/%.s
	$(dir_guard)
	$(CC) -c $< -o $@

$(AOS_WRAPPER_PATH)/obj/$(SUB_BUILD_PATH)/%.o: $(AOS_WRAPPER_PATH)/src/%.cpp $(AOS_WRAPPER_PATH)/src/%.hpp
	$(dir_guard)
	$(CPPC) $(AOS_WRAPPER_CPP_FLAGS) -c $< -o $@

$(MUI_COMPONENTS_PATH)/obj/$(SUB_BUILD_PATH)/%.o: $(MUI_COMPONENTS_PATH)/src/%.cpp $(MUI_COMPONENTS_PATH)/src/%.hpp
	$(dir_guard)
	$(CPPC) $(CPP_FLAGS) -c $< -o $@
