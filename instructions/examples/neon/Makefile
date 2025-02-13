SHELL = bash
include ../../../tlbuild.mk


CC = gcc
CFLAGS := -O0 -g -ggdb
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

#CFLAGS += -mfpu=neon

all: $(TARGETS)

# add objects here
vrsqrtsq_f32: vrsqrtsq_f32.o
vst1q_u8: vst1q_u8.o
vaddq_s64: vaddq_s64.o
neon-sve: neon-sve.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) $(CFLAGS) -o $(@) $(^) $(STATIC_OPTS) $(LDLIBS)

test:
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f $(TARGETS) *.o
