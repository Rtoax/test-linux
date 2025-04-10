#pragma once

#define SYSFS_VMLINUX	"/sys/kernel/btf/vmlinux"

int btf_check_ksym_existence(const char *ksym_name);
