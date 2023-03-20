README
======

# 流程

[https://gcc.gnu.org/wiki/AutoFDO/Tutorial](https://gcc.gnu.org/wiki/AutoFDO/Tutorial)

1. 原始编译运行

```
$ gcc sort.c -o sort.out
./sort.out
```

2. 优化等级

```
$ gcc -O3 sort.c -o sort_optimized-O3.out
./sort_optimized-O3.out
```

3. 生成剖析数据 sort.gcda

```
$ gcc sort.c -o sort_instrumented.out -fprofile-generate
./sort_instrumented.out 

```

4. 使用剖析数据优化编译

```
$ gcc -O3 sort.c -o sort_fdo.out -fprofile-use=sort.gcda
./sort_fdo.out
```

## 简化流程脚本

先后执行

```
./compile.sh
./run.sh
```

## 验证 TLB 命中率

> perf使用方法见 `test/linux/cmd/perf/TLB-loads.sh`.

```
sudo perf stat -e dTLB-loads,dTLB-loads-misses,iTLB-loads,iTLB-loads-misses ./sort.out
```

