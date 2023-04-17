CC = clang
CFLAGS := -Werror -Wall -pthread

define cacheline
endef

all: cachelinesize
	@echo "Compile struct"
	@$(CC) $(CFLAGS) -o struct struct.c -DL3_CACHELINE_SIZE=$(shell ./cachelinesize)

cachelinesize:
	@echo "Compile cachelinesize"
	@$(CC) $(CFLAGS) cachelinesize.c -o cachelinesize

clean:
	@rm -f *.o *.d cachelinesize struct
