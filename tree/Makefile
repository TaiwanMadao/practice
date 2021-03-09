ifeq (0,$(MAKELEVEL))

.SUFFIXES:

INCDIR = $(dir $(shell pwd))

%:: $(INCDIR);

$(INCDIR):
	@ $(MAKE) --no-print-directory -I$@ $(MAKECMDGOALS)

.PHONY: $(INCDIR)

Makefile:;

else #(0,$(MAKELEVEL))

include setup.mk 

ifeq (,$(filter _%,$(notdir $(CURDIR))))

include target.mk

else #(,$(filter _%,$(notdir $(CURDIR))))

SRCDIR := ..

SRCS := $(notdir $(wildcard $(SRCDIR)/*.c))

OBJS := $(SRCS:.c=.o)

HDRDIR := ../../util

CPPFLAGS := $(addprefix -I,$(HDRDIR))

TARGET := $(SRCS:%.c=%)

vpath %.c $(SRCDIR)

vpath %.h $(HDRDIR)

all: $(TARGET);

%: %.c

%: %.o

%: %.o
	$(info GEN $@; LINK $^)
	@ $(LINK.o) $^ $(LOADLIBES) $(LDLIBS) -o $@

.PHONY: all

include autodep.mk

endif #(,$(filter _%,$(notdir $(CURDIR))))

endif #(0,$(MAKELEVEL))
