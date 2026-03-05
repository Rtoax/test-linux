target-y += ceil
target-y += copysign
target-y += exp
target-y += exp2
target-y += fpclassify
target-y += finite
target-y += sqrt sqrt-stress
target-y += nan
target-y += isgreater
target-y += log log-stress
target-y += sin
target-y += signbit
target-y += nextafter
target-y += __Float32x4_t
target-y += __Float64x2_t

LDFLAGS := -lm

CFLAGS_sqrt-stress := -DSTRESS=1
CFLAGS_log-stress := -DSTRESS=1

target-clean-y := clean-tmp

include main.mk

ceil: ceil.o
exp: exp.o
exp2: exp2.o
sqrt: sqrt.o
sqrt-stress: sqrt-stress.o
copysign: copysign.o
fpclassify: fpclassify.o
finite: finite.o
nan: nan.o
isgreater: isgreater.o
log: log.o
log-stress: log-stress.o
sin: sin.o
signbit: signbit.o
nextafter: nextafter.o
__Float32x4_t: __Float32x4_t.o
__Float64x2_t: __Float64x2_t.o

clean-tmp:
	${Q}rm -rf tmpd-* tmp-*
