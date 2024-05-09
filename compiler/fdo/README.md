FDO
===

* FDO: Feedback Directed Optimization
* FDO: Feedback Driven Optimization
* PGO: Profile Guided Optimization
	* Profile guided optimization (PGO), also known as profile-directed feedback (PDF)
* PDF: Profile Directed Feedback
* PFO: Profile Feedback Optimization


# 注意点

- 当使用`-O0`编译时，FDO相关参数不生效；
- 函数或数据cacheline对齐的情况下，优化效果较佳；


# GCC

可能在编译过程需要额外添加 `-fprofile-arcs`, `-ftest-coverage`.
在链接过程需要添加 `-fprofile-arcs`。


# Links

- AutoFDO: [https://github.com/google/autofdo](https://github.com/google/autofdo)
	- Mergo to [GCC](https://github.com/gcc-mirror/gcc), 但是还会做小的修改.
- BOLT: [https://github.com/facebookincubator/BOLT](https://github.com/facebookincubator/BOLT)
	- Merge to [LLVM](https://github.com/llvm/llvm-project.git), BOLT will not be updated.

