##############################################################################
#
# examples of invoking this Makefile:
# building configurations: Debug (default), Release, and Spy
# make
# make CONF=rel
# make clean   # cleanup the build
#

#-----------------------------------------------------------------------------
# project name:
#
PROJECT := blinky

#-----------------------------------------------------------------------------
# libs directories:
#
ELPP = ./libs/easyloggingpp
QPCPP = ./libs/qpcpp
# SOCKETS = ./libs/socket-2.3.9.7
SOCKETS = ./libs/Sockets-2.3.9.9
TINYXML = ./libs/tinyxml2

# list of all source directories used by this project
VPATH := ./app \

# list of all include directories needed by this project
INCLUDES := -I./ \
			-I./app \
			-I$(ELPP) \
			-I$(QPCPP)/include \
			-I$(QPCPP)/src \
			-I$(QPCPP)/ports/posix \
			-I$(SOCKETS) \
			-I$(TINYXML)


#-----------------------------------------------------------------------------
# project files:
#

# C source files...
C_SRCS :=

# C++ source files...
CPP_SRCS := \
	main.cpp \
	qpapp.cpp \
	blinky.cpp \
	thread.cpp \
	log.cpp \

LIB_DIRS  :=
LIBS      := -lpthread

# defines...
# QP_API_VERSION controls the QP API compatibility; 9999 means the latest API
DEFINES   := 

ifeq (,$(CONF))
	CONF := dbg
endif

#-----------------------------------------------------------------------------
# add QP/C++ framework (depends on the OS this Makefile runs on):
#

LIBS += -lqpcpp -lSockets -ltinyxml2

#============================================================================
# Typically you should not need to change anything below this line


#-----------------------------------------------------------------------------
# GNU toolset:
#
# NOTE:
# GNU toolset (MinGW) is included in the QTools collection for Windows, see:
#     http://sourceforge.net/projects/qpc/files/QTools/
# It is assumed that %QTOOLS%\bin directory is added to the PATH
#
CC    := gcc
CPP   := g++
#LINK  := gcc    # for C programs
LINK  := g++   # for C++ programs

#-----------------------------------------------------------------------------
# basic utilities (depends on the OS this Makefile runs on):
#
ifeq ($(OS),Windows_NT)
	MKDIR      := mkdir
	RM         := rm
	TARGET_EXT := .exe
else ifeq ($(OSTYPE),cygwin)
	MKDIR      := mkdir -p
	RM         := rm -f
	TARGET_EXT := .exe
else
	MKDIR      := mkdir -p
	RM         := rm -f
	TARGET_EXT :=
endif

#-----------------------------------------------------------------------------
# build configurations...

ifeq (rel, $(CONF)) # Release configuration ..................................

BIN_DIR := build_rel
# gcc options:
CFLAGS  = -c -O3 -fno-pie -std=c99 -pedantic -Wall -Wextra -W \
	$(INCLUDES) $(DEFINES) -DNDEBUG

CPPFLAGS = -c -O3 -fno-pie -std=c++0x -pedantic -Wall -Wextra \
	-frtti -fexceptions \
	$(INCLUDES) $(DEFINES) -DNDEBUG

LIB_DIRS  += -L./libs/x86/rel

else ifeq (spy, $(CONF))  # Spy configuration ................................

BIN_DIR := build_spy

CPP_SRCS += $(QS_SRCS)
VPATH    += $(QPCPP)/src/qs

# gcc options:
CFLAGS  = -c -g -O -fno-pie -std=c99 -pedantic -Wall -Wextra -W \
	$(INCLUDES) $(DEFINES) -DQ_SPY

CPPFLAGS = -c -g -O -fno-pie -std=c++0x -pedantic -Wall -Wextra \
	-fno-rtti -fexceptions \
	$(INCLUDES) $(DEFINES) -DQ_SPY

else # default Debug configuration .........................................

BIN_DIR := build

# gcc options:
CFLAGS  = -c -g -O -fno-pie -std=c99 -pedantic -Wall -Wextra -W \
	$(INCLUDES) $(DEFINES)

CPPFLAGS = -c -g -O -std=c++0x \
	$(INCLUDES) $(DEFINES)

LIB_DIRS  += -L./libs/x86/dbg

endif  # .....................................................................

LINKFLAGS := -no-pie

#-----------------------------------------------------------------------------
_CC_SRCS	 := $(filter %.cc, $(CPP_SRCS))
_CPP_SRCS	 := $(filter %.cpp, $(CPP_SRCS))
C_OBJS       := $(patsubst %.c,%.o,   $(C_SRCS))
CPP_OBJS     := $(patsubst %.cpp,%.o, $(_CPP_SRCS))
CPP_OBJS     += $(patsubst %.cc,%.o, $(_CC_SRCS))

TARGET_EXE   := $(BIN_DIR)/$(PROJECT)$(TARGET_EXT)
C_OBJS_EXT   := $(addprefix $(BIN_DIR)/, $(C_OBJS))
C_DEPS_EXT   := $(patsubst %.o,%.d, $(C_OBJS_EXT))
CPP_OBJS_EXT := $(addprefix $(BIN_DIR)/, $(CPP_OBJS))
CPP_DEPS_EXT := $(patsubst %.o,%.d, $(CPP_OBJS_EXT))

# create $(BIN_DIR) if it does not exist
ifeq ("$(wildcard $(BIN_DIR))","")
$(shell $(MKDIR) $(BIN_DIR))
endif

#-----------------------------------------------------------------------------
# rules
#

all: version $(TARGET_EXE)

$(TARGET_EXE) : $(C_OBJS_EXT) $(CPP_OBJS_EXT)
	$(LINK) $(LINKFLAGS) $(LIB_DIRS) -o $@ $^ $(LIBS)
	cp $(TARGET_EXE) ./

$(BIN_DIR)/%.d : %.c
	$(CC) -MM -MT $(@:.d=.o) $(CFLAGS) $< > $@

$(BIN_DIR)/%.d : %.cpp
	$(CPP) -MM -MT $(@:.d=.o) $(CPPFLAGS) $< > $@

$(BIN_DIR)/%.d : %.cc
	$(CPP) -MM -MT $(@:.d=.o) $(CPPFLAGS) $< > $@

$(BIN_DIR)/%.o : %.c
	$(CC) $(CFLAGS) $< -o $@

$(BIN_DIR)/%.o : %.cpp
	$(CPP) $(CPPFLAGS) $< -o $@

$(BIN_DIR)/%.o : %.cc
	$(CPP) $(CPPFLAGS) $< -o $@

version:
	sh version.sh

.PHONY : clean show

# include dependency files only if our goal depends on their existence
ifneq ($(MAKECMDGOALS),clean)
  ifneq ($(MAKECMDGOALS),show)
-include $(C_DEPS_EXT) $(CPP_DEPS_EXT)
  endif
endif

.PHONY : clean show

clean :
	-$(RM) $(BIN_DIR)/*.o \
	$(BIN_DIR)/*.d \
	$(TARGET_EXE)

show :
	@echo PROJECT      = $(PROJECT)
	@echo TARGET_EXE   = $(TARGET_EXE)
	@echo VPATH        = $(VPATH)
	@echo C_SRCS       = $(C_SRCS)
	@echo CPP_SRCS     = $(CPP_SRCS)
	@echo C_DEPS_EXT   = $(C_DEPS_EXT)
	@echo C_OBJS_EXT   = $(C_OBJS_EXT)
	@echo C_DEPS_EXT   = $(C_DEPS_EXT)
	@echo CPP_DEPS_EXT = $(CPP_DEPS_EXT)
	@echo CPP_OBJS_EXT = $(CPP_OBJS_EXT)
	@echo LIB_DIRS     = $(LIB_DIRS)
	@echo LIBS         = $(LIBS)
	@echo DEFINES      = $(DEFINES)

