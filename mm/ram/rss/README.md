RSS - Resident Set Size 常驻内存集合大小
=======================================

RSS 常驻内存集合大小，表示相应进程在RAM中占用了多少内存，并不包含在SWAP中占用的虚拟内存。即使是在内存中的使用了共享库的内存大小也一并计算在内，包含了完整的在stack和heap中的内存。

VSZ （Virtual Memory Size)，表明是虚拟内存大小，表明了该进程可以访问的所有内存，包括被交换的内存和共享库内存。


# 查看

```
$ cat /proc/$$/status | grep -i rss
VmRSS:	    6312 kB
RssAnon:	    2200 kB
RssFile:	    4112 kB
RssShmem:	       0 kB

$ ps -p $$ -eo rss
  RSS
 6312
```
