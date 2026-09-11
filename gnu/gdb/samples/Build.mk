include gdb.mk

subdir-y += cpp

target-y += set-value
target-y += set-value-func
target-y += set-value-volatile
target-y += pthread-gdb
target-y += hello
target-y += fork
target-y += linklist
target-y += daxpy

prep-y := hello.strip

prog-y += args.sh
prog-y += break.sh
prog-y += define.sh
prog-y += directory.sh
prog-y += disassemble.sh
prog-y += dump-memory.sh
prog-y += finish.sh
prog-y += fork.sh
prog-y += frame.sh
prog-y += info-address.sh
prog-y += info.sh
prog-y += info-symbol.sh
prog-y += layout.sh
prog-y += list.sh
prog-$(call gdb_gt,8,2) += mmap-file.sh
prog-y += print.sh
prog-y += pthread-gdb.sh
prog-y += ptype.sh
prog-y += set-value.sh
prog-y += show.sh
prog-y += signal.sh
prog-y += symbol-file.sh
prog-y += symbol-value.sh
prog-y += until.sh
prog-y += watch.sh
prog-y += whatis.sh
prog-y += while.sh
prog-y += x.sh

PROG_ENVS_layout.sh := --tty

CFLAGS += -O0 -ggdb
LDFLAGS += -pthread

CFLAGS_hello := -Wno-error=unused-function
