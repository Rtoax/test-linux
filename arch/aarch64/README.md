ARM64(aarch64)
===============

# ARM64 包含 4 个异常等级

- `EL0`：非特权模式，常用来跑**应用程序**；
- `EL1`：特权模式，常用来跑**内核**；
- `EL2`：虚拟化监控程序，例如**Hypervisor**；
- `EL3`：安全模式，例如**Secure Monitor**;


# ARM64 启动级别

启动分为`BL1`,`BL2`,`BL31`,`BL32`,`BL33`阶段:

1. 芯片启动后首先执行`BL1`阶段代码，接着验签启动`BL2`
2. `BL2`根据具体设计启动`BL31`或者`BL33`
3. `BL32`只有在有`BL31`时才可能会存在并被验签加载启动


# ARM64 分为 Secure World 和 Non-Secure World(Normal World)


