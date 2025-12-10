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


# Links

- https://docs.nvidia.com/gpudirect-storage/index.html
