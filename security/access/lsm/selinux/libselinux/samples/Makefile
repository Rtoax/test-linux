
TARGETS += getpidcon

CC = gcc
CFLAGS := -lselinux

build: $(TARGETS)

getpidcon: getpidcon.o

$(TARGETS): %:
	$(CC) $(CFLAGS) -o $(@) $(<)

clean:
	rm -rf $(TARGETS) *.o
