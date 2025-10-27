Crash Kdump
===========

# Trigger crash

```
$ echo c | sudo tee /proc/sysrq-trigger
```


# Start crash

```bash
$ sudo crash /usr/lib/debug/lib/modules/$(uname -r)/vmlinux vmcore
```


# Links

- https://github.com/crash-utility/crash
