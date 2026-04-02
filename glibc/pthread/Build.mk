include arch.mk

subdir-y := cache-misses
subdir-y += out-of-order
subdir-y += samples
subdir-y += scripts
subdir-${IS_X86_64} += pthread_self
