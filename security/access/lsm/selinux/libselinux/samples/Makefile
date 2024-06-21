TARGETS :=
TARGETS += getpidcon

CC = gcc
CFLAGS := -lselinux

build: $(TARGETS)

getpidcon: getpidcon.o

$(TARGETS): %:
	@echo -e "LD   \033[1;32m$(@)\033[m"
	@$(CC) $(CFLAGS) -o $(@) $(<)

clean:
	rm -rf $(TARGETS) *.o
