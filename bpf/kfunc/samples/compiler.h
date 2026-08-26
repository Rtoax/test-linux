#pragma once

#ifndef __ksym
#define __ksym __attribute__((section(".ksyms")))
#endif
#ifndef __weak
#define __weak __attribute__((weak))
#endif
