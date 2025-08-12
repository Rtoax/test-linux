targets :=
targets += ceil
targets += copysign
targets += exp
targets += exp2
targets += fpclassify
targets += finite
targets += sqrt sqrt-stress
targets += nan
targets += isgreater
targets += log log-stress
targets += sin
targets += signbit
targets += nextafter

CC := gcc

CFLAGS :=
CFLAGS += -lm

LDFLAGS := ${CFLAGS}

CFLAGS_sqrt-stress := -DSTRESS=1
CFLAGS_log-stress := -DSTRESS=1

targets-clean := clean-tmp

include ../../template/main.mk

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

clean-tmp:
	${Q}rm -rf tmpd-* tmp-*
