include file.mk

subdir-y += libselinux
subdir-$(call fexist, /sys/fs/selinux) += selinuxfs
