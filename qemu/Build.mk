include qemu.mk

subdir-y += tcg
subdir-y += qcow2

target-prog-${HAVE_QEMU_NBD} += qemu-nbd.sh
target-prog-y += support-cpu.sh
target-prog-y += support-machine.sh
