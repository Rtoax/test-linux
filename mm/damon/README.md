DAMON (Data Access MONitor)
===========================

DAMON is a Linux kernel subsystem that provides a framework for data access monitoring and the monitoring results based system operations. The core monitoring mechanisms of DAMON (refer to Design for the detail) make it

- `accurate` (the monitoring output is useful enough for DRAM level memory management; It might not appropriate for CPU Cache levels, though),
- `light-weight` (the monitoring overhead is low enough to be applied online), and
- `scalable` (the upper-bound of the overhead is in constant range regardless of the size of target workloads).

# Links

- https://docs.kernel.org/mm/damon/index.html

