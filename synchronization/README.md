Synchronization
===============

- atomic: 原子操作
- rcu: Read Copy Update

# Compiler

## __sync

```
type __sync_fetch_and_add (type *ptr, type value, ...)
type __sync_fetch_and_sub (type *ptr, type value, ...)
type __sync_fetch_and_or (type *ptr, type value, ...)
type __sync_fetch_and_and (type *ptr, type value, ...)
type __sync_fetch_and_xor (type *ptr, type value, ...)
type __sync_fetch_and_nand (type *ptr, type value, ...)

{ tmp = *ptr; *ptr op= value; return tmp; }
{ tmp = *ptr; *ptr = ~(tmp & value); return tmp; }   // nand
```

```
type __sync_add_and_fetch (type *ptr, type value, ...)
type __sync_sub_and_fetch (type *ptr, type value, ...)
type __sync_or_and_fetch (type *ptr, type value, ...)
type __sync_and_and_fetch (type *ptr, type value, ...)
type __sync_xor_and_fetch (type *ptr, type value, ...)
type __sync_nand_and_fetch (type *ptr, type value, ...)

{ *ptr op= value; return *ptr; }
{ *ptr = ~(*ptr & value); return *ptr; }   // nand
```

# Q&A

- Q: insmod 失败

```bash
$ sudo insmod completion.ko
insmod: ERROR: could not insert module completion.ko: Key was rejected by service
$ dmesg
...
[   43.493148] Loading of unsigned module is rejected
```

- A: 关闭 Secure Boot.


# Links

- https://gcc.gnu.org/onlinedocs/gcc-4.5.2/gcc/Atomic-Builtins.html

