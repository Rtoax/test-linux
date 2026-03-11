target-y += mtrace
target-y += mprobe
target-y += mcheck_check_all

LDFLAGS += -lmcheck
CFLAGS_mprobe := -Wno-error=use-after-free
