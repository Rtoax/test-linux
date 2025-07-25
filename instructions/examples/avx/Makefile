LLVM_CONFIG = $(shell which llvm-config 2>/dev/null)
LLVM_AS = $(shell which llvm-as 2>/dev/null)
LLVM_DIS = $(shell which llvm-dis 2>/dev/null)
LLC = $(shell which llc 2>/dev/null)

targets :=
targets += sum
targets += sum-avx
targets += sum-avx2
targets += cpu-features
targets += test-asm
targets += avx512_aux
targets += mul-avx256
targets += mul-avx512
targets += add_pd-avx256
targets += add_pd-avx512
targets += add-2dim
targets += ctrl_flow-f4
targets += reducetion-f4
targets += add-unalign-f4
targets += cvt-df
targets += mask

targets-asm := vperm2i128
targets-asm += vfmadd231ps
targets-asm += kxord

CFLAGS += -g -ggdb
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

include ../../../template/main.mk

sum: sum.o
sum-avx: sum-avx.o
sum-avx2: sum-avx2.o
cpu-features: cpu-features.o
test-asm: test-asm.S.o test-asm.o
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
vperm2i128: vperm2i128.asm.o
vfmadd231ps: vfmadd231ps.asm.o
kxord: kxord.asm.o

# FIXME: move to main.mk??
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
