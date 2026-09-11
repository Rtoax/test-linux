======
Darwin
======

Darwin 是苹果公司发布的开源操作系统核心，构成了 macOS 和 iOS 的底层基础。它本身不是完整的 macOS，因为 Finder、Dock、Aqua 界面、Cocoa 框架等上层图形部分并不开源；开源的核心部分叫 Darwin。


XNU 内核
--------

XNU 是 Darwin 的内核，全称 “X is Not Unix”。它混合了：

Mach 微内核：来自卡内基梅隆大学，负责进程、线程、内存管理、IPC

BSD 子系统：来自 FreeBSD / NeXT，提供 Unix 系统调用、文件系统、网络栈、权限模型

I/O Kit：苹果的驱动框架

所以 Darwin 的内核不是 Linux，而是 XNU。


BSD 用户态
----------

Darwin 的用户态基础工具大多来自 BSD 世界，而不是 GNU。比如常见的 ls、cp、sh 等，在 macOS 上是 BSD 版本，不是 GNU coreutils 版本。

因此 macOS 上很多命令的行为和 Linux 上略有不同，例如参数支持、输出格式。


libSystem
---------

Linux 上 C 标准库通常是 glibc。Darwin/macOS 上不是 glibc，而是 libSystem。


Links
-----

-  https://github.com/tpoechtrager/osxcross.git
