include file.mk

subdir-$(call file_exists,/sys/fs/pstore) += pstore
