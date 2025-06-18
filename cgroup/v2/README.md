cgroup V2
=========

- cgroup v2 是 cgroup Linux API 的下一个版本。
- 与 cgroup v1 不同的是， cgroup v2 只有一个层次结构，而不是每个控制器有一个不同的层次结构。

新版本对 cgroup v1 进行了多项改进，其中一些改进是：

* 更简洁、更易于使用的 API
* 可将安全子树委派给容器
* 更新的功能，如压力失速信息（Pressure Stall Information）


# /sys/fs/cgroup/

- memory.max: bytes


# Refs

* [Linux Documentation: Control Group v2](https://www.kernel.org/doc/Documentation/cgroup-v2.txt)
* [K8s 容器运行时](https://kubernetes.io/zh/docs/setup/production-environment/container-runtimes/)
