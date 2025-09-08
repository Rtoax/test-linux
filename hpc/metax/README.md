MetaX - 沐曦
============

# 基本信息

- MXMACA SDK 软件包列表及其源码，包括：编译器、核心库等，是否会提供RPM格式软件包；
- 带内管理 mx-smi，提供带外管理接口；
- 虚拟化支持：SR-IOV，VT-x，SVM，MMIO，IOMMU/SMMU
  - x86: `iommu=pt/iommu.passthrough=1`, `intel_iommu=on/intel_iommu=on`
  - arm: `iommu.passthrough=1`
  - 支持VMware ESXi，Qemu/KVM及其实现的云平台软件，例如 OpenStack
  - 虚拟机x86平台建议 Q35
- 容器支持：


# 性能

- 当动态并行功能启动时，无论核函数是否调用别的核函数，系统软件和核函数的开销将增加。该开销来自设备运行时所需要准备的资源以及设备端启动核函数，并可能导致性能下降。通常，这种开销是由链接到设备运行时库的应用程序产生的。


# 软件栈

- mcTriton: 基于 [Triton](https://github.com/triton-lang/triton) 增加后端
- mcTracer: 支持抓取的数据类型包括: MXMACA Runtime API, MXMACA Kernel, MCTX自定义标签段数据
- mcThrust: 基于标准化模板库STL的C++模板库
- mcSPARSE: 稀疏矩阵和向量的基本线性代数子程序
- mcSolverIT: 稀疏线性系统迭代求解器和预条件子
- mcSOLVER: LAPACK功能，例如稠密矩阵的常用矩阵分解和三角求解例程、稀疏最小而成求解和特征值求解
- mcRAND: 伪随机数和准随机数
- mcPy: 兼容 NumPy 并使用曦云系列 GPU 进行计算加速的 Python 工具库
- mcPyTorch: 在PyTorch的基础上增加了 MXMACA® 后端
- mcProfiler: 是一个可视化的 GPU 性能指标分析工具
- mcJPEG: 提供常用图像格式的编解码
- mcFFT: 快速傅里叶变换
- mcFaiss: 基于 Faiss 实现，提供多种向量搜索算法，提供多种语言的接口，支持多种向量数据的应用
- mcEigen: 用 C++ 实现的开源线性代数库
- mcDNN: 深度神经网络
- mcDF: 处理 DataFrame 数据对象的 Python 计算库
- mcCUB: 并行原语和实用程序
- MCCL: MetaX Collective Communications Library, 提供 GPU 间通信原语的库
- mcBLAS: 线性代数
- mcApex: 在 Apex 的基础上增加了 MXMACA®后端
- 训练框架: PyTorch, PaddlePaddle, Tensorflow
- 推理引擎: MacaRT


# 兼容适配

- warm reset 适配了 H3C UniServer R5300 G6 服务器（有些服务器存在 warm reset 后 GPU 卡无法识别或者无法正常工作等问题）
- 沐曦 GPU 的 MXMACA 软件栈与 CUDA 软件栈高度兼容，可直接利用 PyTorch 中已有的 CUDA DispatchKey 进行适配


# Tools

## mx-diagease

- 内存诊断
- PCIe 诊断
- GPU Stress 诊断
- MetaXLink 诊断
- 电源管理诊断
- PCIe ACS 检查
- IOMMU 检查
- 主机 CPU 工作模式检查


# Questions

## 性能调优

> 是否有类似 **NVIDIA Nsight** 一样的工具

- mcProfiler 都支持哪些指标
- 系统级的性能分析工具?
- 内核级的性能分析工具?
- 调试和性能分析工具?
- GPU 崩溃转储收集工具?
- 检测内存带宽瓶颈（如全局内存访问效率）?
  - 例子：用 Nsight Systems 发现 60% 时间消耗在 CPU-GPU 数据传输
- GPU 硬件断点调试?
- API 追踪
  - 记录所有 GPU API 调用?
  - 重放执行过程诊断错误?

## 编译器: 除后端实现外是否优化

- LLVM:
- OpenACC:
- Triton:
- mcThrust/mcSPARSE: 所有标准库 API 都将运行在加速器上？


# SMI

- **ht-smi**
- **ht-smi topo**
	- commit d74b9ae9bf9b ("metax: README: Mars X203: OAM topo matrix")
	- commit a7a937db7c36 ("metax: README: Mars X203: OAM topo nic mlx")

# Benchmark

- **htvs devices**
	- commit ad678fdf7eff ("metax: README: Mars X203: htvs devices")
- **htvs marslink benchmark [--mode=<ingress|egress>]**
	- commit e139156c8b3a ("metax: README: Mars X203: htvs marslink benchmark")
	- commit 29f83a76d02c ("metax: README: Mars X203: htvs marslink benchmark egress")
	- commit 80e62047d2e7 ("metax: README: Mars X203: htvs marslink benchmark ingress")
- **htvs marslink parallel unidirection**
	- commit c903304dd6b2 ("metax: README: Mars X203: htvs marslink parallel unidirection egress")
	- commit d82133790ed6 ("metax: README: Mars X203: htvs marslink parallel unidirection ingress")
- **htvs memory benchmark**
	- commit 324df728388a ("metax: README: Mars X203: htvs memory benchmark")
	- commit 781d99ebebb7 ("metax: README: Mars X203: htvs memory benchmark kernel-copy")
	- display **htvs memory bandwidth**
		- commit 6c0ad155239f ("metax: README: Mars X203: htvs memory bandwidth")
- **htvs ops**
	- commit af116c3af0a5 ("metax: README: Mars X203: htvs ops")
	- **htvs ops -m fp16 and power**
		- commit 25ae9af043a3 ("metax: README: Mars X203: htvs ops fp16 power")


# Links

- [主页](https://www.metax-tech.com/)
- [沐曦开发者社区](https://developer.metax-tech.com/developer/index)
	- Account: 2386499836@qq.com rongtao
- [软件中心](https://sw-download.metax-tech.com/index)
- [沐曦在线编译平台](https://compiler.metax-tech.com/editor)

## 《沐曦异构并行计算软件栈》

- 在线文档： https://m.zhangyue.com/readbook/13155075/4.html
- 示例代码： https://gitee.com/Inkstoneydz/mxmaca-training-series-for-uestc
