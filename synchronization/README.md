Synchronization
===============

# Compiler

- `__sync`
- `__atomic`


# Kernel


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

