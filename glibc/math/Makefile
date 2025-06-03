TARGETS :=
TARGETS += ceil
TARGETS += copysign
TARGETS += exp
TARGETS += fpclassify
TARGETS += finite
TARGETS += sqrt sqrt-stress
TARGETS += nan
TARGETS += isgreater
TARGETS += log log-stress
TARGETS += sin
TARGETS += signbit
TARGETS += nextafter

CC := gcc

CFLAGS := -Werror -Wall
CFLAGS += -lm

LDFLAGS := ${CFLAGS}

CFLAGS_sqrt-stress := -DSTRESS=1
CFLAGS_log-stress := -DSTRESS=1

TARGETS_CLEAN := clean-tmp

include ../../template/main.mk

ceil: ceil.o
exp: exp.o
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
	${Q}rm -f ${TARGETS} *.o *.d *.log
	${Q}rm -rf tmpd-* tmp-*
