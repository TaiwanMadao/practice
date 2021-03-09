
ifeq (,$(filter %.c,$(SRCS)))

$(error SRCS should not be empty!)

endif #(,$(filter %.c,$(SRCS)))

.SUFFIXES:

DEPDIR := .deps

DEPFLAGS = -MT $@ -MF $(DEPDIR)/$*.d -MMD -MP

POSTCOMPILE = touch $@

#vpath %.d $(DEPDIR)

%.o:: %.c $(DEPDIR)/%.d| $(DEPDIR)
	$(info GEN $@; COMPILE $<)
	@ $(COMPILE.c) $(OUTPUT_OPTION) $(DEPFLAGS) $<
	@ $(POSTCOMPILE)

$(DEPDIR):
	@ [ -d $@ ] || mkdir -p $@

DEPFILES = $(SRCS:%.c=$(DEPDIR)/%.d)

$(DEPFILES):;

#%.d:;

.PRECIOUS: %.o %.d

include $(wildcard $(DEPDIR)/*.d)
