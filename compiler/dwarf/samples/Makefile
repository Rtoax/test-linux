targets := hello
targets-post := hello.dwz hello.strip

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

%.dwz: %
	$(call log_tgt_exe,DWZ,$(<),$(@))
	${Q}cp $(<) $(<).orig
	${Q}dwz $(<) -o $(<).dwz

%.strip: %
	$(call log_tgt_exe,STRIP,$(<),$(@))
	${Q}strip --strip-debug $(<) -o $(<).no-debug
	${Q}eu-strip $(<) -f $(<).debug -o $(<).strip
	${Q}objcopy --strip-debug $(<)
