SHELL = bash
CC = gcc
CFLAGS :=
RUN_PFX :=
TARGETS :=

ifeq ($(shell lscpu | grep -w -e sve -e sve2),)
$(warning Not support SVE/SVE2 on this CPU)
else
TARGETS += sve-width
TARGETS += add_array
TARGETS += svaddlb
CFLAGS += -DCPU_HAVE_SVE=1
endif

TARGETS += neon-sve

# Cross compile
ifdef CROSS_COMPILE
  ifneq ($(shell uname -m),aarch64)
    CC = aarch64-linux-gnu-gcc
    AS = aarch64-linux-gnu-as
    LD = aarch64-linux-gnu-ld
    # This root could be created by Docker Image Tar Archive
    # see: aarch64-linux-gnu-gcc -print-sysroot
    CFLAGS += --sysroot=$(shell pwd)/sysroot
    RUN_PFX = qemu-aarch64 --sysroot=$(shell pwd)/sysroot
  endif
endif

ifeq ($(shell uname -m),aarch64)
  CFLAGS += -march=armv8-a+sve2
  CFLAGS += -DCPU_HAVE_NEON=1
endif

ifdef STATIC
  CFLAGS += -static
endif

all: $(TARGETS)

sve-width: sve-width.o
add_array: add_array.o
svaddlb: svaddlb.o
neon-sve: neon-sve.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	@$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	@$(CC) -o $(@) $(^) $(LDLIBS) $(LDFLAGS) $(LDFLAGS_$(*)) $(CFLAGS) $(CFLAGS_$(*))

test:
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"
	$(RUN_PFX) ./sve-width

clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	@rm -f $(TARGETS) *.o
