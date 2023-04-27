#pragma once

int open_dev_kvm(void);
void check_cap_user_memory(int kvmfd);
int create_vm(int kvmfd);
