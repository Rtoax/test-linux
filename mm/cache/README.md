Cache
=========


# TLB and cacheline

- VIVT (virtual index, virtual tag): Armv4,Armv5
- PIPT (physical index, physical tag):
- PIVT (physical index, virtual tag): MIPS R6000
- VIPT (virtual index, physical tag): Armv8,Intel,AMD


# cache and pagecache

1. dcache (dentry slab)
2. pagecache


```bash
$ echo 3 > /proc/sys/vm/drop_caches
```

其中`3` 表示：

```c
int drop_caches_sysctl_handler(struct ctl_table *table, int write,
		void *buffer, size_t *length, loff_t *ppos)
{
	...
		if (sysctl_drop_caches & 1) {
			iterate_supers(drop_pagecache_sb, NULL);
			count_vm_event(DROP_PAGECACHE);
		}
		if (sysctl_drop_caches & 2) {
			drop_slab();
			count_vm_event(DROP_SLAB);
		}
	...
}
```

从而分为两种

* `drop_pagecache_sb()`
* `drop_slab()`


# Links

* [Documentation for /proc/sys/vm/](https://www.kernel.org/doc/html/latest/admin-guide/sysctl/vm.html)
