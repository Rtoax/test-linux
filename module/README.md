Linux Kernel Module
===================

# ELF

```
$ strip --strip-debug input.ko -o output-no-debug.ko
```

# cmdline

```
rd.driver.blacklist=nouveau modprobe.blacklist=nouveau
```

# Links

- Patch [arm64: module: improve module VA range selection](https://lore.kernel.org/all/20230530110328.2213762-1-mark.rutland@arm.com/)
