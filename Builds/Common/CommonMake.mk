###

#SHELL = /bin/tcsh
LIBTYPE ?= opt

# try to guess the OSGCONFIG path

OSGCONFIG := notset

# use OSGPOOL if set

OSGPOOL ?= ..

# try to get configured information first, will not work if more
# than one system is configured from one dir. Just for the 1.0

OSGINSTALLPREFIX := notset

OPENSG_BASE_DIR ?= /usr

OSGINSTALLPREFIX := $(OPENSG_BASE_DIR)

#PREFIXSUFFIX := $(shell $(OSGPOOL)/CommonConf/config.guess)
#-include .prefix.$(PREFIXSUFFIX)

ifneq ($(OSGINSTALLPREFIX),notset)
    OSGCONFIG := $(OSGINSTALLPREFIX)/bin/osg-config
endif

ifneq ($(OSGROOT),notset)
	OSGCONF := $(wildcard $(OSGROOT)/bin/osg-config)

    ifneq ($(OSGCONF),)
		OSGCONFIG := $(OSGCONF)
	endif

endif

# if configure info wasn't found, maybe a Builds/* install?
ifeq ($(OSGCONFIG),notset)
    INSTALLROOT := $(wildcard ../Builds/$(shell ../CommonConf/config.guess)-*)
    OSGCONF := $(wildcard $(INSTALLROOT)/bin/osg-config)
    ifneq ($(OSGCONF),)
        OSGCONFIG := $(OSGCONF)
    endif
endif

# maybe we can find it in the path?
ifeq ($(OSGCONFIG),notset)
    OSGCONF := \
       $(shell if which osg-config >/dev/null 2>&1; then which osg-config; fi )  
    OSGCONF := $(strip $(OSGCONF))
    ifneq ($(OSGCONF),)
        OSGCONFIG := $(OSGCONF)
    endif
endif

# ok, give up
ifeq ($(OSGCONFIG),notset)
    $(error Can't find osg-config, please configure the Makefile or \
            add it to your PATH)
endif

# Set the system we're running on
SYSTEM := $(shell uname)

# which extension to be used for executables
EXEEXT :=

# be very careful with these lines. There needs to be a space after the Unix
# lines and nothing after the win lines!!

ifeq ($(SYSTEM),IRIX)
        CCOUT := -o 
        LDOUT := -o 
	LINK  := 
        SHARED_LIB_EXT := so
	SHARED_LINK := -shared
endif
ifeq ($(SYSTEM),IRIX64)
        CCOUT := -o 
        LDOUT := -o 
	LINK  := 
endif
ifeq ($(SYSTEM),Linux)
        CCOUT := -o 
        LDOUT := -o 
        LINK i := 
        WINDOW_SYSTEM := X
endif
ifeq ($(findstring WIN,$(SYSTEM)),WIN)
        OS := WIN32
        CCOUT := -Fo
        LDOUT := /out:
	LINK   := -link
	EXEEXT :=.exe
endif
ifeq ($(SYSTEM),HP-UX)
        CCOUT := -o 
        LDOUT := -o 
	LINK  := 
endif
ifeq ($(SYSTEM),Darwin)
        CCOUT := -o 
        LDOUT := -oi
        WINDOW_SYSTEM := Carbon
        LINK  :=
endif

# Var settings

CC = `$(OSGCONFIG) --compiler`

CCFLAGS = `$(OSGCONFIG) --cflags --$(LIBTYPE) Base System $(WINDOW_SYSTEM)`

LDFLAGS = $(LINK) `$(OSGCONFIG) --libs --$(LIBTYPE) Base System $(WINDOW_SYSTEM)`

ifeq ($(LIBTYPE),dbg)
	DGB_OPT_EXT := D
endif

build:	$(APP_NAME)
        
default:	build
        
build:	$(APP_NAME)

$(APP_NAME): $(OBJECTS)
	$(CC) $(LDOUT) $(APP_NAME) $(OBJECTS) $(LDFLAGS) $(EXTRA_LDFLAGS)
        
%.o: %.cpp
	$(CC) -c $(CCFLAGS) $(EXTRA_CCFLAGS) $<

%: %.o
	$(CC) $(LDOUT)$@ $< $(LDFLAGS)

install:	build
	cp $(APP_NAME) $(installdir)/bin
# -----------------------------------------------------------------------------
# Clean-up.
# -----------------------------------------------------------------------------
clean:
	rm -f $(APP_NAME) $(OBJECTS) *core     \
          so_locations *.?db

