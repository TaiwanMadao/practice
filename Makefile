include setup.mk

#SUBDIRS = sort string tree
SUBDIRS	= sort

all clean:
	@ $(foreach 1,$(SUBDIRS),$(MAKE) $@ -I$(CURDIR) -C $(1); )

.PHONY: all clean
