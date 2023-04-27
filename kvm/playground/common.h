#pragma once

int open_dev_kvm(void);
int create_vm(int kvmfd);

void check_cap_user_memory(int kvmfd);
void check_cap_ext_cpuid(int kvmfd);
void check_cap_ext_emul_cpuid(int kvmfd);

