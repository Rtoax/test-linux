TARGETS := loginuid
TARGETS += pagemap
TARGETS += mem
TARGETS += maps

all: $(TARGETS)

loginuid: loginuid.o
pagemap: pagemap.o
mem: mem.o
maps: maps.o

clean:
	rm -f $(TARGETS) *.o *.so
