#pragma once
#define imemb()        __asm__ __volatile__("imemb" : : : "memory")
#define cpu_relax()    imemb()
