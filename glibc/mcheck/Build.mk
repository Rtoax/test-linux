target-y += mtrace
target-y += mprobe
target-y += mcheck_check_all

prog-y += $(filter-out mprobe mcheck_check_all, ${target-y})

LDFLAGS += -lmcheck
CFLAGS_mprobe := -Wno-error=use-after-free
