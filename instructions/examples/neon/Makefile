
CC = gcc
CFLAGS := -O0 -g -ggdb
TARGETS :=

TARGETS += vrsqrtsq_f32
TARGETS += vst1q_u8
TARGETS += vaddq_s64
TARGETS += neon-sve

#CFLAGS += -mfpu=neon

all: $(TARGETS)

# add objects here
vrsqrtsq_f32: vrsqrtsq_f32.o
vst1q_u8: vst1q_u8.o
vaddq_s64: vaddq_s64.o
neon-sve: neon-sve.o

clean:
	rm -f $(TARGETS) *.o
