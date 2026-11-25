include cestc/lingspeed.mk

prog-y += blkio.sh
prog-y += cake.sh
prog-y += cpu.sh
prog-y += file.sh
prog-${HAVE_LINGSPEED_GPU} += lingspeed-mem.sh
prog-y += loadavg.sh
prog-y += memory.sh
prog-y += net.sh
prog-y += normal-distribution.sh
prog-y += open.sh
prog-y += process.sh
prog-y += pulse.sh
prog-y += syscall.sh
prog-y += trigonometric-functions.sh
prog-y += txrx.sh
prog-y += vfs.sh

PROG_ARGS_blkio.sh := --tmout 2s
PROG_ARGS_cake.sh := --tmout 2s
PROG_ARGS_cpu.sh := -- --tmout 2s
PROG_ARGS_file.sh := --tmout 2s
PROG_ARGS_lingspeed-mem.sh := --tmout 2s
PROG_ARGS_loadavg.sh := -- --tmout 2s
PROG_ARGS_memory.sh := -- --tmout 2s
PROG_ARGS_net.sh := --tmout 2s
PROG_ARGS_normal-distribution.sh := --tmout 2s
PROG_ARGS_open.sh := --tmout 2s
PROG_ARGS_process.sh := --tmout 2s
PROG_ARGS_pulse.sh := --tmout 2s
PROG_ARGS_syscall.sh := --tmout 2s
PROG_ARGS_trigonometric-functions.sh := --tmout 2s
PROG_ARGS_txrx.sh := --tmout 2s
PROG_ARGS_vfs.sh := --tmout 2s
