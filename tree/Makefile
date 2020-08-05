TARGET	= demo
NAMES	= heap thread
#SOURCES	= $(addsuffix .c,$(NAMES))
OBJECTS	= $(addsuffix .o,$(NAMES))

CINCS = 

.PHONY: clean

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@

%o: $c
	$(CC) $(CFLAGS) -o $@ -c $<
	
clean:
	@ -rm *.o