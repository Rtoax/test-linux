
TARGETS :=
TARGETS += sum
TARGETS += sum-avx
TARGETS += sum-avx2

all: $(TARGETS)

CFLAGS += -g -ggdb
CFLAGS += -D_GNU_SOURCE
CFLAGS += -O0

CFLAGS_sum := -DTYPE_FLOAT
CFLAGS_sum-avx := -DTYPE_FLOAT -mavx
CFLAGS_sum-avx2 := -DTYPE_FLOAT -mavx2

sum: sum.o
sum-avx: sum-avx.o
sum-avx2: sum-avx2.o

%.o: %.c
	@echo -e "Compile  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)
	objdump -d $(@) > $(@).obj.s

$(TARGETS): %:
	@echo -e "Target   \033[1;32m$(@)\033[m"
	@$(CC) $(CFLAGS) -o $(@) $(^) $(LDLIBS)

test:
	@echo "empty"

clean:
	rm -f $(TARGETS) *.o *.obj.s
