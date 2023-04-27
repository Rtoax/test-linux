#pragma once

int open_dev_kvm(void);
int create_vm(int kvmfd);
int create_vcpu(int vmfd);

void check_cap_user_memory(int kvmfd);
void check_cap_ext_cpuid(int kvmfd);
void check_cap_ext_emul_cpuid(int kvmfd);
void check_cap_get_msr_features(int kvm);

