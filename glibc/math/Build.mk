target-y += ceil
target-y += copysign
target-y += exp
target-y += exp2
target-y += fpclassify
target-y += finite
target-y += sqrt sqrt-stress
target-y += nan
target-y += isgreater
target-y += log log-stress log2 log10
target-y += sin
target-y += signbit
target-y += nextafter
target-${IS_AARCH64} += __Float32x4_t
target-${IS_AARCH64} += __Float64x2_t
target-${IS_AARCH64} += __SVFloat32_t
target-${IS_AARCH64} += __SVFloat64_t
target-${IS_AARCH64} += __SVBool_t

target-clean-y := clean-tmp

log10-objs := log.1.o
log2-objs := log.2.o

LDFLAGS := -lm

CFLAGS_sqrt-stress := -DSTRESS=1
CFLAGS_log-stress := -DSTRESS=1
CFLAGS_log.1 := -DLOG10=1
CFLAGS_log.2 := -DLOG2=1
