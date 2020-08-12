.SUFFIXES:

ifndef _ARCH

_ARCH := $(PRINT_ARCH)

endif

OBJDIR := _$(_ARCH)

#MAKETARGET = $(MAKE) --no-print-directory $(MAKECMDGOALS) -f ../Makefile -C $@

%: $(OBJDIR); 

$(OBJDIR):
	@ [ -d $@ ] || mkdir -p $@
	@ $(MAKE) --no-print-directory $(MAKECMDGOALS) -f ../Makefile -C $@

.PHONY: $(OBJDIR)

Makefile:;
%.mk:;
