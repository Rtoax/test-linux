CPU - Central Processor Units
=============================

# Kernel Commandline

- `isolcpus=1-3`


# APIs

- `sysconf(_SC_NPROCESSORS_CONF)`, `get_nprocs_conf()`
- `sysconf(_SC_NPROCESSORS_ONLN)`, `get_nprocs()`


# Commands

- `chcpu`: configure CPUs


# lscpu

- /proc/cpuinfo
- /sys/devices/system/cpu
- /sys/devices/system/cpu/online


# Links

- wikepedia: [Die shot](https://en.wikipedia.org/wiki/Die_shot)
  - `/sys/devices/system/cpu/cpu0/topology/die_id`
