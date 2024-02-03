Memory Managment
============


# 进程内存类型

见`/proc/1/smaps`

- `RSS`(Resident Set Size): 驻留内存，进程占用物理内存的大小
- `PSS`(Proportional Set Size): 如五个进程的动态库占用`50pages`，统计到一个进程的PSS为`10 Pages`
- `USS`(Unique Set Size): 仅代表进程私有内存

```bash
$ sudo dnf install smem
$ sudo apt-get install smem
```

```bash
$ smem
  PID User     Command                         Swap      USS      PSS      RSS
26301 rongtao  cat                                0      104      128     1884
26302 rongtao  cat                                0      104      128     1884
 2633 rongtao  dbus-broker --log 4 --contr        0      304      382     2592
```


# 用户态内存管理

- jemalloc
- tcmalloc

