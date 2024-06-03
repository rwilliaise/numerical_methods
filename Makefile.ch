CC=gcc
CFLAGS=$(shell pkg-config --cflags raylib) -Wall -g -I../base
LDFLAGS=$(shell pkg-config --libs raylib) -lm
BASE_OBJECTS=../base/nm.o

all: $(foreach obj,$(OBJECTS),$(basename $(obj)))
clean:
	rm -f $(BASE_OBJECTS) $(foreach obj,$(OBJECTS),$(obj))
	rm -f $(foreach obj,$(OBJECTS),$(basename $(obj)))

# gorgeous
define NEWLINE

endef

$(foreach obj,$(OBJECTS),$(basename $(obj)): $(obj) $(BASE_OBJECTS)$(NEWLINE))

.PHONY: all clean
