CC = clang
CFLAGS := -Werror -Wall -pthread

define cacheline
	@echo "Compile cachelinesize"
	@gcc cachelinesize.c -o cachelinesize
endef

all:
	$(call cacheline)
	@echo "Compile struct"
	@$(CC) $(CFLAGS) -o struct struct.c -DL3_CACHELINE_SIZE=$(shell ./cachelinesize)


clean:
	@rm -f *.o *.d cachelinesize struct
