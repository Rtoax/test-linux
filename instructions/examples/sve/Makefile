
CC = gcc

TARGETS :=
TARGETS += sve-width

CFLAGS += -march=armv8-a+sve

all: $(TARGETS)

sve-width-asm: sve-width-asm.o
sve-width-intrinsics: sve-width-intrinsics.o


clean:
        rm -f $(TARGETS) *.o