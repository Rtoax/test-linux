include file.mk

subdir-y += libselinux
subdir-$(call file_exists, /sys/fs/selinux) += selinuxfs
