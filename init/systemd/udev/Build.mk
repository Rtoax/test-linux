include systemd/udev.mk

subdir-y += bootctl
subdir-y += kernel-install
subdir-${HAVE_SYSTEMD_LIBUDEV_H} += libudev
