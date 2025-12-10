GPUDirect Storage
=================


```
┌──────────────┐
│              │
│     CPU      │
│              │
└───────┬──────┘
        │
        │
┌───────┴──────┐           read
│              ┝━━━━━━━━━━━━━━━━━━━━━━━━━━┓
│     RAM      │                          ┃
│              ◀───────────────────┐      ┃
└───▲──────┬───┘           write   │      ┃
    ┃      │                       │      ┃
read┃      │write                  │      ┃
    ┃      │                       │      ┃
    ┃      │                       │      ┃
    ┃      │                       │      ┃
┌───┸──────▼───┐     write     ┌───┴──────▼───┐
│              ◀═══════════════╡              │
│   Storage    │   GPUDirect   │     HBM      │
│              ╞═══════════════▶              │
└──────────────┘     read      └──────┬───────┘
                                      │
                                      │
                               ┌──────┴───────┐
                               │              │
                               │     GPU      │
                               │              │
                               └──────────────┘
```


# Enable GDS

## Lingspeed

```
$ sudo modprobe lingspeed mas=1
```


# Examples

1. Running on GPU 0 (`-d 0`), write (`-I 1`) to NVMe (`-D /mnt/nvme`) file (`-f a.out`), transfer data from GPU to Storage (`-x 0`) directly with size 4G (`-s 4G`) single thread (`-w 1`).

```
$ sudo ./gdsio -D /mnt/nvme/ -f a.out -d 0 -x 0 -I 1 -s 4G -w 1
```


# Links

- https://docs.nvidia.com/gpudirect-storage/index.html
