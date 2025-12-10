GPUDirect Storage
=================


```
┌──────────────┐           read
│              ┝━━━━━━━━━━━━━━━━━━━━━━━━━━┓
│     CPU      │                          ┃
│              ◀───────────────────┐      ┃
└───▲──────┬───┘           write   │      ┃
    ┃      │                       │      ┃
read┃      │write                  │      ┃
    ┃      │                       │      ┃
    ┃      │                       │      ┃
    ┃      │                       │      ┃
┌───┸──────▼───┐     write     ┌───┴──────▼───┐
│              ◀═══════════════╡              │
│   Storage    │   GPUDirect   │     GPU      │
│              ╞═══════════════▶              │
└──────────────┘     read      └──────────────┘
```


# Enable GDS

## Lingspeed

```
$ sudo modprobe lingspeed mas=1
```


# Links

- https://docs.nvidia.com/gpudirect-storage/index.html
