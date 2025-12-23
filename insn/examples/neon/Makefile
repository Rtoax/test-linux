include arch.mk
include cpu.mk

target-y += vrsqrtsq_f32
target-y += vst1q_u8
target-y += vaddq_s64
target-y += neon-sve

CFLAGS += ${cpu-feature-cflags}
CFLAGS += -march=armv8-a+sve2

include main.mk

vrsqrtsq_f32: vrsqrtsq_f32.o
vst1q_u8: vst1q_u8.o
vaddq_s64: vaddq_s64.o
neon-sve: neon-sve.o
