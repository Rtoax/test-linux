Linux Kernel security, Capabilities and Seccomp
===============================================

Compiling this program is very straightforward, you just do a:

```bash
$ clang filter-write.c -o filter-write
```

The program is made to filter any write syscall that happens, if you try it
using a command that is supposed to write it will not print anything.


Let's first do a command that prints stuff, like `ls -la`:

```bash
$ ls -la
total 44
drwxr-xr-x. 2 rongtao rongtao   121 Oct 27 17:05 .
drwxr-xr-x. 3 rongtao rongtao    36 Jun  6  2022 ..
-rwxr-xr-x  1 rongtao rongtao 18888 Oct 27 17:01 filter-write
-rw-r--r--. 1 rongtao rongtao  1175 Jun  6  2022 filter-write.c
-rw-r--r--  1 rongtao rongtao  5960 Oct 27 17:01 filter-write.o
-rw-r--r--  1 rongtao rongtao    14 Aug  9 20:28 .gitignore
-rw-r--r--  1 rongtao rongtao   683 Aug  9 20:27 Makefile
-rw-r--r--. 1 rongtao rongtao  2208 Oct 27 17:05 README.md
```

Now let's do the same with `filter-write`:

```
$ ./filter-write "ls -la"
```

No output! Let's see why!

We can use `strace` to dig into this:

```bash
$ strace --follow-forks ./filter-write "ls -la"
[pid 37782] write(1, "drwxr-xr-x. 2 rongtao rongtao   "..., 51) = -1 EPERM (Operation not permitted)
[pid 37782] write(1, "drwxr-xr-x. 3 rongtao rongtao   "..., 52) = -1 EPERM (Operation not permitted)
[pid 37782] write(1, "-rwxr-xr-x  1 rongtao rongtao 18"..., 62) = -1 EPERM (Operation not permitted)
[pid 37782] write(1, "-rw-r--r--. 1 rongtao rongtao  1"..., 64) = -1 EPERM (Operation not permitted)
[pid 37782] write(1, "-rw-r--r--  1 rongtao rongtao  5"..., 64) = -1 EPERM (Operation not permitted)
[pid 37782] write(1, "-rw-r--r--  1 rongtao rongtao   "..., 60) = -1 EPERM (Operation not permitted)
[pid 37782] write(1, "-rw-r--r--  1 rongtao rongtao   "..., 58) = -1 EPERM (Operation not permitted)
[pid 37782] write(1, "-rw-r--r--. 1 rongtao rongtao  1"..., 59) = -1 EPERM (Operation not permitted)
```

All the write syscalls got `EPERM`.
