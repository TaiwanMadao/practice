CFLAGS := -Wall -Wextra -Werror -std=c99 -pedantic

CURDIR = $(eval CURDIR := $$(shell pwd))$(CURDIR)

PRINT_ARCH = $(shell uname -m)

ifdef DEBUG

CFLAGS += -g3

else #DEBUG

CFLAGS += -O3

endif #DEBUG
