#pragma once
int sys_memfd_create(const char *name, unsigned int flags);
int sys_memfd_secret(unsigned int flags);
