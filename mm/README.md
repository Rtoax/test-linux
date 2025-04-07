MM - Memory Managment
====================


# 进程内存类型

见`/proc/1/smaps`

- `RSS`(Resident Set Size): 驻留内存，进程占用物理内存的大小
- `PSS`(Proportional Set Size): 如五个进程的动态库占用`50pages`，统计到一个进程的PSS为`10 Pages`
- `USS`(Unique Set Size): 仅代表进程私有内存

```bash
$ sudo dnf install smem
$ sudo apt-get install smem
```

# Tools

## smem

```bash
$ smem
  PID User     Command                         Swap      USS      PSS      RSS
218967 rongtao  cat                                0      104      131     1848
218968 rongtao  cat                                0      112      141     1928
218980 rongtao  /usr/libexec/cgroupify app-        0      248      327     2880
```


# 用户态内存管理

- jemalloc
- tcmalloc


# Links

- v5.8 [Memory Layout on AArch64 Linux](https://www.kernel.org/doc/html/v5.8/arm64/memory.html)
