README
======

# 编译

直接执行两个编译脚本即可。

- gcc: compile-gcc.sh
- clang: compile-clang.sh

> gcc 编译过程需要执行 create_gcov 来获取代码覆盖信息，需要安装 AutoFDO.
> [AutoFDO git仓库](https://github.com/google/autofdo.git)


## 运行测试

直接执行编译出的可执行文件即可。


## 验证 TLB 命中率

```
$ sudo perf stat -e dTLB-loads,dTLB-loads-misses,iTLB-loads,iTLB-loads-misses ./sort.out
```


# 参考链接

- [https://gcc.gnu.org/wiki/AutoFDO/Tutorial](https://gcc.gnu.org/wiki/AutoFDO/Tutorial)
