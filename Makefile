
#Compiler and Linker
CC          := gcc
GCC         := gcc

#The Target Binary Program
TARGET      := main
SHAREDLIBTARGET := libfoo
TESTTARGET  := test_suite

#The Directories, Source, Includes, Objects, Binary and Resources
SRCDIR      := src
EXTDIR      := ext
TESTDIR     := test
INCDIR      := inc
BUILDDIR    := obj
TARGETDIR   := bin
RESDIR      := res
SRCEXT      := c
DEPEXT      := d
OBJEXT      := o
LIBEXT      := so
LIBDIR      := lib
LIBFILES    := $(wildcard lib/*.so)
LIBLINK     := $(addprefix -l, $(LIBFILES))

current_dir = $(shell pwd)

#Flags, Libraries and Includes
CXXSTD      := -Wno-deprecated-register -g -O0
CFLAGS      := $(CXXSTD) -fopenmp -Wall -O3 -g
DYNLIBPARAM := -dynamiclib
INC         := -I$(INCDIR) -I/usr/local/include -Isrc -Isrc/test -I$(EXTDIR) -I/c/MinGW/msys/1.0/local/include
LINKLIB     := -L$(LIBDIR) -L/c/MinGW/msys/1.0/local/lib
SHAREDPARAM := -shared

PROGRAMFILES := $(shell find $(SRCDIR)/ -type f -name "*.$(SRCEXT)")
TESTFILES  := $(shell find $(TESTDIR)/ $(SRCDIR)/ ! -name 'main.c' -type f -name "*.$(SRCEXT)" )
OBJECTS     := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(PROGRAMFILES:.$(SRCEXT)=.$(OBJEXT)))

all: directories main tests

directories:
	mkdir -p $(TARGETDIR)
	mkdir -p $(BUILDDIR)
	mkdir -p $(TESTDIR)
	mkdir -p $(INCDIR)

main_nodeps:
	$(CC) $(CXXSTD) $(INC) $(LINKLIB) $(LIBLINK) $(PROGRAMFILES) -lm -o $(TARGETDIR)/$(TARGET)

main: $(OBJECTS)
	$(CC) $(LINKLIB) $(LIBLINK) -o $(TARGETDIR)/$(TARGET) $^

sharedlib: $(OBJECTS)
	$(CC) $(SHAREDPARAM) -o $(LIBDIR)/$(SHAREDLIBTARGET).$(LIBEXT) $^

print-%  : ; @echo $* = $($*)

$(BUILDDIR)/%.$(OBJEXT): $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(dir $@)
	$(CC) $(CXXSTD) $(INC) -c -o $@ $<
	@$(CC) $(CXXSTD) $(INC) -MM $(SRCDIR)/$*.$(SRCEXT) > $(BUILDDIR)/$*.$(DEPEXT)
	@cp -f $(BUILDDIR)/$*.$(DEPEXT) $(BUILDDIR)/$*.$(DEPEXT).tmp
	@sed -e 's|.*:|$(BUILDDIR)/$*.$(OBJEXT):|' < $(BUILDDIR)/$*.$(DEPEXT).tmp > $(BUILDDIR)/$*.$(DEPEXT)
	@sed -e 's/.*://' -e 's/\\$$//' < $(BUILDDIR)/$*.$(DEPEXT).tmp | fmt -1 | sed -e 's/^ *//' -e 's/$$/:/' >> $(BUILDDIR)/$*.$(DEPEXT)
	@rm -f $(BUILDDIR)/$*.$(DEPEXT).tmp

tests:
	$(CC) $(CXXSTD) $(INC) $(LINKLIB) $(TESTFILES) -lcspec -lm -o $(TARGETDIR)/$(TESTTARGET)

.PHONY: all tests clean
clean:
	rm -rf obj && mkdir obj
	rm -rf bin/* obj/*
