
TARGETS :=
TARGETS += sum
TARGETS += sum-avx
TARGETS += sum-avx2
TARGETS += cpu-features
TARGETS += test-asm
TARGETS += avx512_aux

all: $(TARGETS)

CFLAGS += -g -ggdb
CFLAGS += -D_GNU_SOURCE
CFLAGS += -O0

CFLAGS_sum := -DTYPE_FLOAT
CFLAGS_sum-avx := -DTYPE_FLOAT -mavx
CFLAGS_sum-avx2 := -DTYPE_FLOAT -mavx2
CFLAGS_test-asm := -std=gnu17
CFLAGS_avx512_aux := -mavx512f

sum: sum.o
sum-avx: sum-avx.o
sum-avx2: sum-avx2.o
cpu-features: cpu-features.o
test-asm: test-asm.oS test-asm.o
avx512_aux: avx512_aux.o

%.o: %.c
	@echo -e "Compile  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)
	objdump -d $(@) > $(@).obj.s

%.oS: %.S
	@echo -e "Compile  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)
	objdump -d $(@) > $(@).obj.s

$(TARGETS): %:
	@echo -e "Target   \033[1;32m$(@)\033[m"
	@$(CC) $(CFLAGS) -o $(@) $(^) $(LDLIBS)

test:
	@echo "empty"

clean:
	rm -f $(TARGETS) *.o *.obj.s *.oS
