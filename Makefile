include setup.mk

SUBDIRS	= sort

export CFLAGS CINCS

#.PHONY: all clean $(SUBDIRS)

#test:
#	$(info $(origin CFLAGS))
#	$(info $(origin CPPFLAGS))
#	$(info $(CFLAGS))
#	$(info $(CPPFLAGS))
#	$(MAKE) -C sort

all clean: $(SUBDIRS)

$(SUBDIRS):
	@ echo "Compile Directory: $@"
	@ $(MAKE) $(MAKECMDGOALS) -C $@

clean:
	@ for d in $(SUBDIRS); \
	do \
		echo "Clean Directory: $$d"; \
		$(MAKE) clean -C $$d; \
	done

#ifeq (,$(filter _%,$(CURDIR)))
#include target.mk
#else

#endif
