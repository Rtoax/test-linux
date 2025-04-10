include ../../../tlbuild.mk


LLVM_CONFIG = $(shell which llvm-config 2>/dev/null)
LLVM_AS = $(shell which llvm-as 2>/dev/null)
LLVM_DIS = $(shell which llvm-dis 2>/dev/null)
LLC = $(shell which llc 2>/dev/null)

CC := gcc

TARGETS :=
TARGETS += sum
TARGETS += sum-avx
TARGETS += sum-avx2
TARGETS += cpu-features
TARGETS += test-asm
TARGETS += avx512_aux
TARGETS += mul-avx256
TARGETS += mul-avx512
TARGETS += add_pd-avx256
TARGETS += add_pd-avx512
TARGETS += add-2dim
TARGETS += ctrl_flow-f4
TARGETS += reducetion-f4
TARGETS += add-unalign-f4
TARGETS += cvt-df
TARGETS += mask

TARGETS_asm := vperm2i128
TARGETS_asm += vfmadd231ps
TARGETS_asm += kxord

all: $(TARGETS) $(TARGETS_asm)

CFLAGS += -g -ggdb
CFLAGS += -D_GNU_SOURCE
CFLAGS += -O0

CFLAGS_sum := -DTYPE_FLOAT
CFLAGS_sum-avx := -DTYPE_FLOAT -mavx
CFLAGS_sum-avx2 := -DTYPE_FLOAT -mavx2
CFLAGS_test-asm := -std=gnu11
CFLAGS_avx512_aux := -mavx512f
# Why -mfma?
# - https://www.cnblogs.com/hellowooorld/p/11529078.html
# - https://www.intel.com/content/www/us/en/docs/intrinsics-guide/index.html#text=_mm256_fmaddsub_ps&ig_expand=3191
CFLAGS_mul-avx256 := -mavx2 -mfma
CFLAGS_mul-avx512 := -mavx512f -mfma
CFLAGS_add_pd-avx256 := -mavx2 -mfma
CFLAGS_add_pd-avx512 := -mavx512f -mfma
CFLAGS_add-2dim := -mavx2 -mfma
CFLAGS_ctrl_flow-f4 := -mavx2 -mfma
CFLAGS_reducetion-f4 := -mavx2 -mfma
CFLAGS_add-unalign-f4 := -mavx2 -mfma
CFLAGS_cvt-df := -mavx2 -mfma
CFLAGS_mask := -mavx2 -mavx512f -mfma

sum: sum.o
sum-avx: sum-avx.o
sum-avx2: sum-avx2.o
cpu-features: cpu-features.o
test-asm: test-asm.oS test-asm.o
avx512_aux: avx512_aux.o
mul-avx256: mul-avx256.o
mul-avx512: mul-avx512.o
add_pd-avx256: add_pd-avx256.o
add_pd-avx512: add_pd-avx512.o
add-2dim: add-2dim.o
ctrl_flow-f4: ctrl_flow-f4.o
reducetion-f4: reducetion-f4.o
add-unalign-f4: add-unalign-f4.o
cvt-df: cvt-df.o
mask: mask.o
vperm2i128: vperm2i128.os
vfmadd231ps: vfmadd231ps.os
kxord: kxord.os

ifeq ($(CC),clang)
  # If clang, i want to get IR
  define clang_emit_llvm
    ${Q}$(CC) $(CFLAGS) $(CFLAGS_$(*)) -S -emit-llvm $(1) -o $(1:.c=.ll)
    @$(LLVM_AS) $(1:.c=.ll) -o $(1:.c=.bc)
    @$(LLVM_DIS) $(1:.c=.bc) -o $(1:.c=.dis.ll)
    @$(LLC) $(1:.c=.ll) -o $(1:.c=.llc.s)
  endef
else
  define clang_emit_llvm
  endef
endif

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)
	@objdump -d $(@) > $(@).obj.s
	$(call clang_emit_llvm,$(<))

%.oS: %.S
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)
	@objdump -d $(@) > $(@).obj.s

%.os: %.asm
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	@nasm -o $(@) -felf64 $(<)

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) $(CFLAGS) -o $(@) $(^)

$(TARGETS_asm): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	@$(LD) -o $(@) $(^)

test:
	@echo -e "  TEST  \033[1;32m$(TARGETS) ${TARGETS_asm}\033[m"
	@echo "empty"

clean:
	@echo -e "  CLEAN \033[1;32m$(TARGETS) $(TARGETS_asm)\033[m"
	${Q}rm -f $(TARGETS) $(TARGETS_asm) \
		*.o *.obj.s *.oS *.os *.ll *.llc.s *.bc
