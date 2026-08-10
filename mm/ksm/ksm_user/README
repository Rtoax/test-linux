Kernel SamePage Merging - 同页合并测试例
========================================

# 步骤

1. 编译源代码

```
gcc test.c 
```

2. 使用 dd 命令创建 ksm.dat.out 文件 , 大小 100M

```
dd if=/dev/zero of=ksm.dat.out bs=1M count=100
```

3. 使能 KSM

```
echo 1 > /sys/kernel/mm/ksm/run
```

4. 运行 test.c 程序

```
./a.out ksm.dat.out
```

5. 查看系统有多少页被 合并 了

```
cat /sys/kernel/mm/ksm/pages_sharing
cat /sys/kernel/mm/ksm/pages_shared
cat /sys/kernel/mm/ksm/pages_unshared
```
