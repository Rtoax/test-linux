README
======

# 编译

直接执行

```bash
# 编译 gcc 的分支测试例
$ ./compile.sh -c clang -t branch
```

> gcc 编译过程需要执行 create_gcov 来获取代码覆盖信息，需要安装 AutoFDO.


## 运行测试

直接执行编译出的可执行文件即可。


## 验证 TLB 命中率

```bash
$ ./stat.sh ./sort.out
```


# 参考链接

- [https://gcc.gnu.org/wiki/AutoFDO/Tutorial](https://gcc.gnu.org/wiki/AutoFDO/Tutorial)
- [AutoFDO git仓库](https://github.com/google/autofdo.git)
- [clang BOLT](https://github.com/llvm/llvm-project)
