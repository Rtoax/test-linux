FDO
===


# 注意点

- 当使用`-O0`编译时，FDO相关参数不生效；
- 函数或数据cacheline对齐的情况下，优化效果较佳；


# GCC

可能在编译过程需要额外添加 `-fprofile-arcs`, `-ftest-coverage`.
在链接过程需要添加 `-fprofile-arcs`。

