New(or NUMA) vDSO
=================

Update the target process's `vdso` code without modifying the target process code.


# Test

```
$ make test
...
7f1ac9255000-7f1ac9259000 r--p 00000000 00:00 0                          [vvar]
7f1ac9259000-7f1ac925b000 r-xp 00000000 08:00 2620452837                 /home/sda/git-repos/ostools/nvDSO/vdso.elf

$ make test DEBUG=1
...
7ff52124e000-7ff521252000 r--p 00000000 00:00 0                          [vvar]
7ff521252000-7ff521254000 r-xp 00000000 00:00 0                          [vdso]
...
7ff52124e000-7ff521252000 r--p 00000000 00:00 0                          [vvar]
7ff521252000-7ff521254000 r-xp 00000000 08:00 2620452836                 /home/sda/git-repos/ostools/nvDSO/vdso.elf
```

If kernel config support `CONFIG_ANON_VMA_NAME`:

```
$ make test DEBUG=1
...
7f4dbf45f000-7f4dbf461000 r--p 00000000 00:00 0                          [vvar]
7f4dbf463000-7f4dbf465000 r-xp 00000000 00:00 0                          [vdso]
...
7f4dbf45f000-7f4dbf461000 r--p 00000000 00:00 0                          [vvar]
7f4dbf463000-7f4dbf465000 r-xp 00000000 00:00 0                          [anon:vdso.new]
```

If kernel config support `CONFIG_ANON_VMA_NAME`, and set envrioment `NVDSO_NAME`:

```
$ NVDSO_NAME=vdso.ostools LD_PRELOAD=./libnvdso.so ./main
...
7fd89107c000-7fd89107e000 r--p 00000000 00:00 0                          [vvar]
7fd891080000-7fd891082000 r-xp 00000000 00:00 0                          [anon:vdso.ostools]
                                                                               ^^^^^^^^^^^^
```

Or just test with:

```
$ NVDSO_DEBUG=1 LD_PRELOAD=./libnvdso.so ./main
```

If you want to use anonymous nvdso, set `NVDSO_ANON` envrioment:

```
$ make test ANON=1
...
7fb70b65e000-7fb70b660000 r--p 00000000 00:00 0                          [vvar]
7fb70b662000-7fb70b664000 r-xp 00000000 00:00 0
                                                                         ^^^^^^
```

Or just test with:

```
$ NVDSO_ANON=1 LD_PRELOAD=./libnvdso.so ./main
```


# Test vDSO physical address with `virt2phy`

Ensure kernel's vDSO physical address's NUMA (here `numa=3`, never change)

```
$ sudo ./virt2phy
Run on CPU 6, NUMA 3
NAME             VIRT_ADDR        PHY_ADDR         MEM_NUMA CPU      CPU_NUMA
vdso text        7f12cc022000     223ebb000        3        6        3
                                                   ^^^^^^^^

# Couldn't change vDSO paddr with `numactl`

$ sudo numactl --cpunodebind=1 ./virt2phy
                             ^^
Run on CPU 2, NUMA 1
NAME             VIRT_ADDR        PHY_ADDR         MEM_NUMA CPU      CPU_NUMA
vdso text        7fb252871000     223ebb000        3        2        1
                                                   ^^
```

Change vDSO physical address with libnvdso.so:

```
$ sudo LD_PRELOAD=./libnvdso.so numactl --cpunodebind=1 ./virt2phy
       ^^^^^^^^^^^^^^^^^^^^^^^^                       ^^
Run on CPU 2, NUMA 1
NAME             VIRT_ADDR        PHY_ADDR         MEM_NUMA CPU      CPU_NUMA
vdso text        7f89391a0000     14b19f000        1        2        1
                                                   ^^

# Test again

$ sudo LD_PRELOAD=./libnvdso.so numactl --cpunodebind=2 ./virt2phy
                                                      ^^
Run on CPU 2, NUMA 1
NAME             VIRT_ADDR        PHY_ADDR         MEM_NUMA CPU      CPU_NUMA
vdso text        7f89391a0000     14b19f000        2        2        1
                                                   ^^
```
