#pragma once
#include <sys/shm.h>

#define PATHNAME	"/etc/os-release"
#define PROJ_ID	1234

#define SVSHM_MODE (SHM_R | SHM_W | SHM_R >> 3 | SHM_R >> 6)

