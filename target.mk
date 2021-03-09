.SUFFIXES:

ifndef _ARCH

_ARCH := $(PRINT_ARCH)

endif #_ARCH

OBJDIR := _$(_ARCH)

ifdef DEBUG

OBJDIR := $(OBJDIR)_debug

endif #DEBUG

# MAKETARGET = $(MAKE) --no-print-directory $(MAKECMDGOALS) -f ../Makefile -C $@

%:: $(OBJDIR); 

$(OBJDIR):
	@ [ -d $@ ] || mkdir -p $@
	@ $(MAKE) --no-print-directory $(MAKECMDGOALS) -f ../Makefile -C $@

.PHONY: $(OBJDIR)

clean:
	$(info RM $(OBJDIR))
	-@ $(RM) $(OBJDIR)

.PHONY: clean

Makefile:;
%.mk:;
