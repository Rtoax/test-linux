subdir-y := breakfast

target-${IS_X86_64} += int3
target-${IS_AARCH64} += brk
