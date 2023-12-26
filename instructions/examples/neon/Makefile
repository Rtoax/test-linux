
CC = gcc
CFLAGS := -O0 -g -ggdb
TARGETS :=

ifeq ($(shell uname -m),aarch64)
TARGETS += vrsqrtsq_f32
TARGETS += vst1q_u8
TARGETS += vaddq_s64
else
CFLAGS += -DCONFIG_NO_NEON=1
endif

TARGETS += neon-sve

ifeq ($(shell lscpu | grep -w -e sve -e sve2),)
$(warning Not support SVE/SVE2 on this CPU)
CFLAGS += -DCONFIG_NO_SVE=1
else
CFLAGS += -march=armv8-a+sve2
endif

#CFLAGS += -mfpu=neon

all: $(TARGETS)

# add objects here
vrsqrtsq_f32: vrsqrtsq_f32.o
vst1q_u8: vst1q_u8.o
vaddq_s64: vaddq_s64.o
neon-sve: neon-sve.o

clean:
	rm -f $(TARGETS) *.o
