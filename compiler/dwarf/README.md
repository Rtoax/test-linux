Dwarf - Debugging With Attributed Record Formats
================================================

- [主页](http://wiki.dwarfstd.org/index.php?title=Main_Page)
- [PDF下载](https://dwarfstd.org/download.html)


`DWARF`调试格式和ELF格式的关系是：`DWARF`是`ELF`最常用的调试信息格式，它不一定与`ELF`相关，但两者是一起发展的，因此在开发中常一起使用。

- `DWARF`格式中，高级语言的源文件、函数、变量、类型等调试信息在`.debug_info`节区中存储;
- 为了节省存储空间，`DWARF`在`.debug_abbrev`节区中定义了所有节点的类型和格式;
- `.debug_info`和`.debug_abbrev`节区中，每个节点表示一种调试信息，例如`DW_TAG_compile_unit`表示源文件调试信息;

例如：

```
$ gcc -g hello.c
$ readelf -S a.out | grep debug
  [27] .debug_aranges    PROGBITS         0000000000000000  00002c0c
  [28] .debug_info       PROGBITS         0000000000000000  00002c3c
  [29] .debug_abbrev     PROGBITS         0000000000000000  00002f66
  [30] .debug_line       PROGBITS         0000000000000000  00003047
  [31] .debug_str        PROGBITS         0000000000000000  0000313b
```


# Sections

## .debug_info .debug_abbrev

这两个节是在一起的两个节，它们是“`实例和类型`”的关系，`.debug_info`节中的内容是`.debug_abbrev`节中的一个结构的实例。在abbrev节中声明了很多中不同的Dwarf类型组合(我们可以想象为C语言中的结构声明，而这些类型都是DWARF格式约定好的类型)，然后在info节的每一项都声明自己使用的是abbrev节中的那个类型，也就是说明自己是那个结构的实例。

- `.debug_info`: dwarfdump --print-info (-i)
- `.debug_abbrev`: dwarfdump --print-abbrev (-b)


## .debug_frame

该节主要是为了表示函数栈帧的关系。也就是当执行一个函数的时候，这个函数中的各个寄存器的存放位置及变化情况，栈帧的计算方法的变化情况等。

- `.debug_frame`: dwarfdump --print-frame (-f)


## .debug_line

这里包含的是行号和机器指令之间的映射关系，这也是实现源代码级调试的重要依据。

- `.debug_line`: dwarfdump --print-lines (-l)


## .debug_str

C语言中的字符串组，它们以零结束，放在一个单独的节是为了提高存储效率。

- `.debug_str`: dwarfdump --print-strings (-s)


# Declaration Information

- https://gcc.gnu.org/wiki/LTO_Reader/Writer

以下内容尚未出现在变量和函数的`DWARF`信息中：

```
DECL_SECTION_NAME
DECL_VISIBILITY
DECL_ONE_ONLY
DECL_COMDAT
DECL_WEAK
DECL_DLLIMPORT_P
DECL_UNINLINABLE
DECL_IS_MALLOC
DECL_IS_RETURNS_TWICE
DECL_IS_PURE
DECL_IS_NOVOPS
DECL_STATIC_CONSTRUCTOR
DECL_STATIC_DESTRUCTOR
DECL_NO_INSTRUMENT_FUNCTION_ENTRY_EXIT
DECL_NO_LIMIT_STACK
DECL_NO_STATIC_CHAIN
DECL_INLINE
DECL_HARD_REGISTER
DECL_HAS_INIT_PRIORITY
DECL_INIT_PRIORITY
DECL_TLS_MODEL
DECL_THREAD_LOCAL_P
DECL_IN_TEXT_SECTION
DECL_COMMON
```

我们不应该盲目地为所有这些字段创建`DWARF`属性。

例如，表示`DECL_INIT_PRIORITY`的正确方法可能是该字段的`DWARF`属性，但表示`DECL_HAS_INIT_PRIORITY`的正确方法可能是由于`DECL_INIT_PRIORITY`的`DWARF`属性不存在而不是单独的位。作为另一个例子，可以计算 `DECL_SECTION_NAME`通过查看`ELF`符号表。


# Links

- [DWARF Debugging Standard Website](https://dwarfstd.org/)
- IDA: https://my.hex-rays.com/dashboard/download-center/
