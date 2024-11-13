Synchronization
===============

- atomic: 原子操作
- rcu: Read Copy Update

# Q&A

## insmod 失败

```bash
$ sudo insmod completion.ko
insmod: ERROR: could not insert module completion.ko: Key was rejected by service
$ dmesg
...
[   43.493148] Loading of unsigned module is rejected
```

> 关闭 Secure Boot.

