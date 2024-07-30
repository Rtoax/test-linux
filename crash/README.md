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
