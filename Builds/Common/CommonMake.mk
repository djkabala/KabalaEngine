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
	SHARED_LIB_EXT := so
	SHARED_LINK := -shared
endif
ifeq ($(SYSTEM),Linux)
        CCOUT := -o 
        LDOUT := -o 
	LINK  := 
	SHARED_LIB_EXT := so
	SHARED_LINK := -shared
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
	SHARED_LIB_EXT := so
	SHARED_LINK := -shared
endif
ifeq ($(SYSTEM),Darwin)
        CCOUT := -o 
        LDOUT := -o 
	LINK  :=
	SHARED_LIB_EXT := dylib
	SHARED_LINK := -dynamiclib
endif

# Var settings

CC = `$(OSGCONFIG) --compiler`

CCFLAGS = `$(OSGCONFIG) --cflags --$(LIBTYPE) Base System`

LDFLAGS = $(LINK) `$(OSGCONFIG) --libs --$(LIBTYPE) Base System`

ifeq ($(LIBTYPE),dbg)
	DGB_OPT_EXT := D
endif
SHARED_LIB_NAME=lib$(LIB_NAME)$(DGB_OPT_EXT).$(SHARED_LIB_EXT)

STATIC_LIB_NAME=lib$(LIB_NAME)$(DGB_OPT_EXT).a

build:	$(SHARED_LIB_NAME) \
	$(STATIC_LIB_NAME)
        
default:	build
        
build:	$(SHARED_LIB_NAME) \
	$(STATIC_LIB_NAME)

$(SHARED_LIB_NAME): $(OBJECTS)
	$(CC) $(SHARED_LINK) $(LDOUT) $(SHARED_LIB_NAME) $(OBJECTS) $(LDFLAGS) $(EXTRA_LDFLAGS)
        
$(STATIC_LIB_NAME): $(OBJECTS)
	ar -ruv $(STATIC_LIB_NAME) $(OBJECTS)

%.o: %.cpp
	$(CC) -c $(CCFLAGS) $(EXTRA_CCFLAGS) $<

%: %.o
	$(CC) $(LDOUT)$@ $< $(LDFLAGS)

install:	build
	@if [ ! -w $(installdir) ]; then                               \
		mkdir $(installdir);                                   \
		fi;
	@if [ ! -w $(installdir)/include ]; then                               \
		mkdir $(installdir)/include;                                   \
		fi;
	@if [ ! -w $(installdir)/include/OpenSG ]; then                               \
		mkdir $(installdir)/include/OpenSG;                                   \
		fi;
	@if [ ! -w $(installdir)/include/OpenSG/$(LIB_INCLUDE_DIR_NAME) ]; then                               \
		mkdir $(installdir)/include/OpenSG/$(LIB_INCLUDE_DIR_NAME);                                   \
		fi;
	@if [ ! -w $(installdir)/lib ]; then                               \
		mkdir $(installdir)/lib;                                   \
		fi;
	@if [ ! -w $(installdir)/bin ]; then                               \
		mkdir $(installdir)/bin;                                   \
		fi;
	$(commondir)/CopyIncludes.sh $(commondir) $(srcdir) $(installdir)/include/OpenSG/$(LIB_INCLUDE_DIR_NAME);
	cp $(SHARED_LIB_NAME) $(installdir)/lib
	cp $(STATIC_LIB_NAME) $(installdir)/lib
# -----------------------------------------------------------------------------
# Clean-up.
# -----------------------------------------------------------------------------
clean:
	rm -f $(SHARED_LIB_NAME) $(STATIC_LIB_NAME) $(OBJECTS) *core     \
          so_locations *.?db
