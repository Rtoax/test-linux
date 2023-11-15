#pragma once

int sys_clock_getres(clockid_t clockid, struct timespec *tp);
int sys_clock_gettime(clockid_t clockid, struct timespec *tp);
