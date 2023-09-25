Device Tree
===========


```
     DTC         Bootloader
DTS ------> DTB ------------> kernel
```

DTS: Device Tree source file
DTC: Device Tree Compiler
DTB: Device Tree binary file (device tree blob)


# /sys/firmware/devicetree/


# 节点格式

```
[label:] <node-name> [@<unit-address>]{
	[property]
	[child nodes]
	...
}
```

- `[]` 可省略
- `<>` 不可省略


## unit-address

- cpu node: 0, 1
- reg node: 0x12010000
