# list

```
$ sudo ndctl list
[
  {
    "dev":"namespace0.0",
    "mode":"raw",
    "size":1073741824,
    "sector_size":512,
    "blockdev":"pmem0"
  }
]
```

# fsdax

```
$ sudo ndctl create-namespace -m fsdax -e namespace0.0 -f
{
  "dev":"namespace0.0",
  "mode":"fsdax",
  "map":"dev",
  "size":"1006.00 MiB (1054.87 MB)",
  "uuid":"c4bd8856-dbc4-46e9-9d01-4bc24c7eea32",
  "sector_size":512,
  "align":2097152,
  "blockdev":"pmem0"
}

$ sudo mkfs.xfs /dev/pmem0
$ sudo mount -o dax /dev/pmem0 pmem/
$ mount | grep dax
/dev/pmem0 on /home/rongtao/pmem type xfs (rw,relatime,seclabel,attr2,dax=always,inode64,logbufs=8,logbsize=32k,noquota)
```

# devdax

```
$ sudo ndctl create-namespace -m devdax -e namespace0.0 -f
{
  "dev":"namespace0.0",
  "mode":"devdax",
  "map":"dev",
  "size":"1006.00 MiB (1054.87 MB)",
  "uuid":"35012086-7b54-4c4c-a1ea-10d984b45902",
  "daxregion":{
    "id":0,
    "size":"1006.00 MiB (1054.87 MB)",
    "align":2097152,
    "devices":[
      {
        "chardev":"dax0.0",
        "size":"1006.00 MiB (1054.87 MB)",
        "target_node":0,
        "align":2097152,
        "mode":"devdax"
      }
    ]
  },
  "align":2097152
}

# create /dev/dax0.0, and use it with mmap(2) like PMDK.
```
