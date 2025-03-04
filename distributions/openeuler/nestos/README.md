NestOS
===========

* [https://gitee.com/openeuler/NestOS](https://gitee.com/openeuler/NestOS)

NestOS是一款在openEuler社区CloudNative sig组孵化的云底座操作系统，专注于提供最佳的容器主机，大规模下安全的运行容器化工作负载。

Nest即“巢穴”，作为可以包容podman（鼹鼠）、iSulad（蚂蚁）、docker（集装箱）的“巢穴”，NestOS即化身为可以搭载iSulad、docker、podman等基础平台的操作系统。

NestOS将配置工具ignition与rpm-ostree、OCI支持、SElinux强化等技术集成在一起，采用基于双系统分区、容器技术和集群架构的设计思路，搭载iSulad、docker、podman等主流容器基础平台，克服了由于用户修改系统内容、用户服务对系统组件依赖，以及系统软件包升级时不稳定中间态等种种导致升级过程不可靠的因素，最终以一种轻量级、定制化的操作系统呈现出来。可以适应各种不同的基础设施环境，并与OKD紧密集成，针对运行Kubernetes进行了优化，使系统具备十分便捷的集群组建能力。


