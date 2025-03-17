Software RAID
================

# fstype

- `lsblk -o +fstype`: FSTYPE field shows `linux_raid_member`;


# Software RAID

见`mdadm`(manage MD devices aka Linux Software RAID).

- Create Software RAID1

```
$ sudo mdadm -C /dev/md0 -ayes -l1 -n2 /dev/xvd[b,c]1
```

- show stat

```
$ cat /proc/mdstat
# Or
$ mdadm -D /dev/md0
```

- Part

```
$ sudo mkfs.ext4 /dev/md0
```

- Emulate bad disk

```
$ sudo mdadm /dev/md1 -f /dev/sdb5
```

- Remove disk

```
$ sudo mdadm /dev/md1 -r /dev/sdb5
```

- Add new disk

```
$ sudo mdadm /dev/md1 -a /dev/sdb7
```

- Stop RAID

```
$ sudo mdadm -S /dev/md1
```

