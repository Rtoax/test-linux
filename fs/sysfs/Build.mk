include kconfig.mk

subdir-y += block
subdir-y += bus
subdir-y += firmware
subdir-${CONFIG_PSTORE} += pstore

prog-y := mounts.sh
