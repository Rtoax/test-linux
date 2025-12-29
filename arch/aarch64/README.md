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


# Cortex

| Cortex           | CPU Part |
| ---------------- | -------- |
| ARM1136j-s       | 0xb36    |
| ARM1156t2-s      | 0xb56    |
| ARM1176jz-s      | 0xb76    |
| ARM810           | 0x810    |
| ARM920           | 0x920    |
| ARM922           | 0x922    |
| ARM926           | 0x926    |
| ARM940           | 0x940    |
| ARM946           | 0x946    |
| ARM966           | 0x966    |
| ARM1020          | 0xa20    |
| ARM1022          | 0xa22    |
| ARM1026          | 0xa26    |
| ARM11 MPCore     | 0xb02    |
| ARM1136          | 0xb36    |
| ARM1156          | 0xb56    |
| ARM1176          | 0xb76    |
| Cortex-A5        | 0xc05    |
| Cortex-A7        | 0xc07    |
| Cortex-A8        | 0xc08    |
| Cortex-A9        | 0xc09    |
| Cortex-A17       | 0xc0d    |
| Cortex-A15       | 0xc0f    |
| Cortex-A17       | 0xc0e    |
| Cortex-R4        | 0xc14    |
| Cortex-R5        | 0xc15    |
| Cortex-R7        | 0xc17    |
| Cortex-R8        | 0xc18    |
| Cortex-M0        | 0xc20    |
| Cortex-M1        | 0xc21    |
| Cortex-M3        | 0xc23    |
| Cortex-M4        | 0xc24    |
| Cortex-M7        | 0xc27    |
| Cortex-M0+       | 0xc60    |
| Cortex-A32       | 0xd01    |
| Cortex-A34       | 0xd02    |
| Cortex-A53       | 0xd03    |
| Cortex-A35       | 0xd04    |
| Cortex-A55       | 0xd05    |
| Cortex-A65       | 0xd06    |
| Cortex-A57       | 0xd07    |
| Cortex-A72       | 0xd08    |
| Cortex-A73       | 0xd09    |
| Cortex-A75       | 0xd0a    |
| Cortex-A76       | 0xd0b    |
| Neoverse-N1      | 0xd0c    |
| Cortex-A77       | 0xd0d    |
| Cortex-A76AE     | 0xd0e    |
| Cortex-R52       | 0xd13    |
| Cortex-R82AE     | 0xd14    |
| Cortex-R82       | 0xd15    |
| Cortex-R52+      | 0xd16    |
| Cortex-M23       | 0xd20    |
| Cortex-M33       | 0xd21    |
| Cortex-M52       | 0xd24    |
| Cortex-M55       | 0xd22    |
| Cortex-M85       | 0xd23    |
| Neoverse-V1      | 0xd40    |
| Cortex-A78       | 0xd41    |
| Cortex-A78AE     | 0xd42    |
| Cortex-A65AE     | 0xd43    |
| Cortex-X1        | 0xd44    |
| Cortex-A510      | 0xd46    |
| Cortex-A710      | 0xd47    |
| Cortex-X2        | 0xd48    |
| Neoverse-N2      | 0xd49    |
| Neoverse-E1      | 0xd4a    |
| Cortex-A78C      | 0xd4b    |
| Cortex-X1C       | 0xd4c    |
| Cortex-A715      | 0xd4d    |
| Cortex-X3        | 0xd4e    |
| Neoverse-V2      | 0xd4f    |
| Cortex-A520      | 0xd80    |
| Cortex-A720      | 0xd81    |
| Cortex-X4        | 0xd82    |
| Neoverse-V3AE    | 0xd83    |
| Neoverse-V3      | 0xd84    |
| Cortex-X925      | 0xd85    |
| Cortex-A725      | 0xd87    |
| Cortex-A520AE    | 0xd88    |
| Cortex-A720AE    | 0xd89    |
| C1-Nano          | 0xd8a    |
| C1-Pro           | 0xd8b    |
| C1-Ultra         | 0xd8c    |
| Neoverse-N3      | 0xd8e    |
| Cortex-A320      | 0xd8f    |
| C1-Premium       | 0xd90    |

> see also util-linux lscpu-arm.c
