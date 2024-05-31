CC=gcc
CFLAGS=$(shell pkg-config --cflags raylib) -Wall -g -I../base
LDFLAGS=$(shell pkg-config --libs raylib) -lm

all: $(foreach obj,$(OBJECTS),$(basename $(obj)))
clean:
	rm -f $(foreach obj,$(OBJECTS),$(obj))
	rm -f $(foreach obj,$(OBJECTS),$(basename $(obj)))

# gorgeous
define NEWLINE

endef

$(foreach obj,$(OBJECTS),$(basename $(obj)): $(obj)$(NEWLINE))

.PHONY: all clean
