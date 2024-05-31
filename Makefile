CHAPTERS=ch2 ch3

all:
	$(foreach CH,$(CHAPTERS),$(MAKE) -C $(CH)/;)

clean:
	$(foreach CH,$(CHAPTERS),$(MAKE) -C $(CH)/ clean;)

.PHONY: all clean
