Software RAID
================


# Software RAID

见`mdadm`(manage MD devices aka Linux Software RAID).

- 创建软RAID1

```
$ sudo mdadm -C /dev/md0 -ayes -l1 -n2 /dev/xvd[b,c]1
```

- 查看状态

```
$ cat /proc/mdstat
# Or
$ mdadm -D /dev/md0
```

- 分区

```
$ sudo mkfs.ext4 /dev/md0
```

- 模拟损坏盘

```
$ sudo mdadm /dev/md1 -f /dev/sdb5
```

- 移除故障盘

```
$ sudo mdadm /dev/md1 -r /dev/sdb5
```

- 添加新硬盘

```
$ sudo mdadm /dev/md1 -a /dev/sdb7
```

- 停止阵列

```
$ sudo mdadm -S /dev/md1
```

