include qemu.mk

subdir-y += tcg
subdir-y += qcow2

prog-${HAVE_QEMU_NBD} += qemu-nbd.sh
prog-y += support-cpu.sh
prog-y += support-machine.sh
