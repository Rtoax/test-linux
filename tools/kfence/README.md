Kernel Electric-Fence (KFENCE)
==============================

* [https://www.kernel.org/doc/html/latest/dev-tools/kfence.html](https://www.kernel.org/doc/html/latest/dev-tools/kfence.html)

Kernel Electric-Fence (KFENCE) is a low-overhead sampling-based memory safety error detector.
KFENCE detects:

* heap out-of-bounds access
* use-after-free
* invalid-free errors

KFENCE is designed to be enabled in production kernels, and has near zero performance overhead. Compared to KASAN, KFENCE trades performance for precision. The main motivation behind KFENCE’s design, is that with enough total uptime KFENCE will detect bugs in code paths not typically exercised by non-production test workloads. One way to quickly achieve a large enough total uptime is when the tool is deployed across a large fleet of machines.

* `CONFIG_KFENCE=y`:
