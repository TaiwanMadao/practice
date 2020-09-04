
ifeq (,$(filter %.c,$(SRCS)))

$(error SRCS should not be empty!)

endif #(,$(filter %.c,$(SRCS)))

#.SUFFIXES:

DEPDIR := .deps

DEPFLAGS = -MT $@ -MF $(DEPDIR)/$*.d -MMD -MP

#vpath %.d $(DEPDIR)

%.o: %.c $(DEPDIR)/%.d| $(DEPDIR)
	$(COMPILE.c) $(OUTPUT_OPTION) $(DEPFLAGS) $<

$(DEPDIR):
	@ [ -d $@ ] || mkdir -p $@

DEPFILES = $(SRCS:%.c=$(DEPDIR)/%.d)

$(DEPFILES):;

#%.d:;

.PRECIOUS: %.o %.d

include $(wildcard $(DEPDIR)/*.d)
