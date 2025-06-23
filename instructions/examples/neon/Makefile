TARGETS :=

ifeq ($(shell uname -m),aarch64)
  TARGETS += vrsqrtsq_f32
  TARGETS += vst1q_u8
  TARGETS += vaddq_s64
  CFLAGS += -DCPU_HAVE_NEON=1
endif

TARGETS += neon-sve

ifeq ($(shell lscpu | grep -w -e sve -e sve2),)
  $(warning WARNING: Not support SVE/SVE2 on this CPU)
else
  CFLAGS += -DCPU_HAVE_SVE=1
  CFLAGS += -march=armv8-a+sve2
endif

include ../../../template/main.mk

vrsqrtsq_f32: vrsqrtsq_f32.o
vst1q_u8: vst1q_u8.o
vaddq_s64: vaddq_s64.o
neon-sve: neon-sve.o
