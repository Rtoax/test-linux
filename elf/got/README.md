GOT: Global Offset Table
========================

`.got`节保存了全局偏移表。`.got`节和`.plt`节一起提供了对导入的共享函数的访问入口，有动态链接器在运行时进行修改。

当一个共享库被加载进一个进程的地址空间中时，一定有指向此共享库的重定位。动态链接器会修改可执行文件中的`GOT`。`GOT`位于数据段`.got.plt`节中。


# GOT 相关 Sections 详细介绍

- `.plt` 保存了一小段代码，外加`foo@plt`代码;
	- 或用独立的`.plt.got`节保存`foo@plt`代码;
- `.got`
	- `.got` entries are never resolved lazily;
	- `.got` 用于存放全局变量的地址和不需要延迟绑定的函数的地址;
	- `.rela.dyn` are `R_X86_64_GLOB_DAT`
- `.got.plt` 保存了 `_GLOBAL_OFFSET_TABLE_`;
	- `.got.plt` entries can be resolved lazily;
	- `.got.plt` 用于存放需要延迟绑定的函数的地址;
	- `.rela.plt` are `R_X86_64_JUMP_SLOT`


# Dynamic Link Procedure

## x86 32bits

```bash
# 调试 32bit 程序
$ gdb ./_GLOBAL_OFFSET_TABLE_-32

# 查看地址空间
(gdb) info proc  mappings
...
	Start Addr   End Addr       Size     Offset  Perms   objfile
	 0x8048000  0x8049000     0x1000        0x0  r--p   _GLOBAL_OFFSET_TABLE_-32
	 0x8049000  0x804a000     0x1000     0x1000  r-xp   _GLOBAL_OFFSET_TABLE_-32
	 0x804a000  0x804b000     0x1000     0x2000  r--p   _GLOBAL_OFFSET_TABLE_-32
	 0x804b000  0x804c000     0x1000     0x2000  r--p   _GLOBAL_OFFSET_TABLE_-32
	 0x804c000  0x804d000     0x1000     0x3000  rw-p   _GLOBAL_OFFSET_TABLE_-32
	0xf7d9d000 0xf7dc0000    0x23000        0x0  r--p   /usr/lib/libc.so.6
	0xf7dc0000 0xf7f1f000   0x15f000    0x23000  r-xp   /usr/lib/libc.so.6
	0xf7f1f000 0xf7f92000    0x73000   0x182000  r--p   /usr/lib/libc.so.6
	0xf7f92000 0xf7f94000     0x2000   0x1f5000  r--p   /usr/lib/libc.so.6
	0xf7f94000 0xf7f95000     0x1000   0x1f7000  rw-p   /usr/lib/libc.so.6
	...
	0xf7fc9000 0xf7fca000     0x1000        0x0  r--p   /usr/lib/ld-linux.so.2
	0xf7fca000 0xf7fed000    0x23000     0x1000  r-xp   /usr/lib/ld-linux.so.2
	0xf7fed000 0xf7ffb000     0xe000    0x24000  r--p   /usr/lib/ld-linux.so.2
	0xf7ffb000 0xf7ffd000     0x2000    0x31000  r--p   /usr/lib/ld-linux.so.2
	0xf7ffd000 0xf7ffe000     0x1000    0x33000  rw-p   /usr/lib/ld-linux.so.2

# 查看 GOT 地址
(gdb) x /x _GLOBAL_OFFSET_TABLE_
0x804bff4:	0xf7ffda200804bf08

# 查看三个 GOT 条目值：GOT[0], GOT[1], GOT[2], GOT[3], GOT[4]
(gdb) p /x _GLOBAL_OFFSET_TABLE_[0]
$5 = 0x804bf08
(gdb) p /x _GLOBAL_OFFSET_TABLE_[1]
$6 = 0xf7ffda20
(gdb) p /x _GLOBAL_OFFSET_TABLE_[2]
$7 = 0xf7fdaf70
(gdb) p /x _GLOBAL_OFFSET_TABLE_[3]
$3 = 0x8049036
(gdb) p /x _GLOBAL_OFFSET_TABLE_[4]
$13 = 0x8049046

# 查看 PLT 条目代码
(gdb) disassemble 'printf@plt'
Dump of assembler code for function printf@plt:
   0x08049040 <+0>:	jmp    *0x804c004
   0x08049046 <+6>:	push   $0x8
   0x0804904b <+11>:	jmp    0x8049020

    # 首先执行 jmp    *0x804c004
    # 这会跳转到 got.plt 条目执行，如下，会执行 0x08049046 的代码。
    # 这就会继续执行 push   $0x8
    (gdb) x /x 0x804c004
    0x804c004 <printf@got.plt>:	0x08049046

    # 执行 push   $0x8
    # 立即数 $0x8 表示偏移

    # 然后执行 jmp    0x8049020
    # 地址 0x8049020 实际是 section .plt 的地址

# 查看地址 0x8049020 内容
(gdb) disassemble /s 0x8049020,+0x8
Dump of assembler code from 0x8049020 to 0x8049030:
  0x08049020:	push   0x804bff8
  0x08049026:	jmp    *0x804bffc

    # 执行 push   0x804bff8
    # 地址为 GOT[1]，保存了 link_map 结构的地址
    # 可以这样查看
    (gdb) p *(struct link_map *)0xf7ffda20
    # 或
    (gdb) p *(struct link_map *)_GLOBAL_OFFSET_TABLE_[1]

    # 执行 jmp    *0x804bffc
    # 地址 0x804bffc 为 GOT[2]，GOT[2]=0xf7fdaf70
    # 那么，跳转到 0xf7fdaf70 执行
    # 这实际上是函数 _dl_runtime_resolve()
    (gdb) disassemble /s 0xf7fdaf70,+0x8
      0xf7fdaf70 <_dl_runtime_resolve+0>:	push   %eax
    # 或者
    (gdb) disassemble /s _GLOBAL_OFFSET_TABLE_[2],+0x8

    # 此时，控制权交给了链接器
```


## x86 64bits diagram

```
   +------------------+                                        +--------------------------+
   | int main(void) { |                                        | ld-linux:                |
   |    printf@plt(); |                                      +-+->  _dl_runtime_resolve() |
   | }     |          |                GOT (.got.plt)        | +------+-------------------+
   +-------+----------+             +-----------------+      |        |
           |                        |                 |      |        |
           |                        +-----------------+      |        |Modify GOT[plt]
           |                        |                 |      |        |
+----------+                        +-----------------+      |        |
|                              +--->|   GOT[2]        +------+        |
|                              |    +-----------------+               |
|     printf@plt()             |    |                 |               |
|  +----------------------+    |    +-----------------+               |
+--+>jmp    *0x2fc2(%rip)-+----+--->| printf@got[plt] +-----+ <-------+
+--+>push   $0x1          |    |    +-----------------+     |
|  | jmp    0x40102 ---+  |    |    |                 |     |                   libc.so
|  +-------------------+--+    |    +-----------------+     |                 +----------+
|                      |       |    |                 |     +---------------->| printf() |
|                      |       |    +-----------------+     |   Second call   +----------+
|                      |       |                            |
|                      |       |                            |
+----------------------+-------+----------------------------+
                       |       |                   First call
                       |       |
+----------------------+       |
|                              |
|       .plt                   |
|   +----------------------+   |
+---> push   0x2fca(%rip)  |   |
    | jmp    *0x2fcc(%rip)-+---+
    +----------------------+
```

