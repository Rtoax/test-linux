include systemd/coredump.mk

subdir-y += journalctl
subdir-${HAVE_COREDUMPCTL} += systemd-coredump
subdir-y += udev
subdir-y += ukify
