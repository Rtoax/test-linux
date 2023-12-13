
CC = gcc
CFLAGS :=
TARGETS :=

TARGETS += vrsqrtsq_f32
TARGETS += vst1q_u8

#CFLAGS += -mfpu=neon

all: $(TARGETS)

# add objects here
vrsqrtsq_f32: vrsqrtsq_f32.o
vst1q_u8: vst1q_u8.o

clean:
	rm -f $(TARGETS) *.o
