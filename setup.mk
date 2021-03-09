CFLAGS := -Wall -Wextra -Werror -std=gnu99 -pedantic

CURDIR = $(eval CURDIR := $$(shell pwd))$(CURDIR)

PRINT_ARCH = $(shell uname -m)

RM = rm -rf

ifdef DEBUG

CFLAGS += -g3

else #DEBUG

CFLAGS += -O3

endif #DEBUG
