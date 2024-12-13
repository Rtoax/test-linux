#pragma once
#if defined(__TARGET_ARCH_x86)
#define SYSCALL_WRAPPER 1
#define SYS_PREFIX "__x64_"
#elif defined(__TARGET_ARCH_arm64)
#define SYSCALL_WRAPPER 1
#define SYS_PREFIX "__arm64_"
#else
#error Not support arch
#endif
