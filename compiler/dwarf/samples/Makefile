CC := gcc

target-y := hello
target-post-y := hello.dwz hello.strip

target-clean-y := clean0

CFLAGS := -g
CFLAGS += -ggdb -O0
ifdef DWARF5
  CFLAGS += -gdwarf-5
else ifdef DWARF4
  CFLAGS += -gdwarf-4
endif

CFLAGS_hello += -Wno-error=unused-variable

include ../../../template/main.mk

hello: hello.o

clean0:
	$(Q)rm -f hello.no-debug hello.debug hello.orig

%.dwz: %
	$(call log_tgt_exe,DWZ,$(<),$(@))
	${Q}cp $(<) $(<).orig
	${Q}dwz $(<) -o $(<).dwz

%.strip: %
	$(call log_tgt_exe,STRIP,$(<),$(@))
	${Q}strip --strip-debug $(<) -o $(<).no-debug
	${Q}eu-strip $(<) -f $(<).debug -o $(<).strip
	${Q}objcopy --strip-debug $(<)
