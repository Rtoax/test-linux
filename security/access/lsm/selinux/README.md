SELinux - Security Enhanced Linux
===================================

# 介绍

* Security-Enhanced Linux (SELinux) 是在内核中实现的强制访问控制 (MAC) 安全机制。
* SELinux 最初是在 CentOS 4 中引入的，并在后来的 CentOS 版本中得到了显着增强。
* 与内核交互数据方式`netlink`, 见`NETLINK_SELINUX`.
* access vector cache (AVC)


# Architecture

## [How does SELinux work?](https://www.redhat.com/en/topics/linux/what-is-selinux)

SELinux defines access controls for the applications, processes, and files on a system. It uses security policies, which are a set of rules that tell SELinux what can or can’t be accessed, to enforce the access allowed by a policy.

When an application or process, known as a subject, makes a request to access an object, like a file, SELinux checks with an access vector cache (AVC), where permissions are cached for subjects and objects.

If SELinux is unable to make a decision about access based on the cached permissions, it sends the request to the security server. The security server checks for the security context of the app or process and the file. Security context is applied from the SELinux policy database. Permission is then granted or denied.

If permission is denied, an "avc: denied" message will be available in /var/log.messages.


# 访问控制

操作系统有两类访问控制：自主访问控制（`DAC`）和强制访问控制（`MAC`）。
标准Linux安全是一种`DAC`，SELinux为Linux增加了一个灵活的和可配置的的`MAC`。


# SELinux Config

configuration: `/etc/selinux/config`
relate commands: `getenforce`, `setenforce`
cmdline: `selinux=0`


# SELinux 模式

SELinux 有三个模式（可以由用户设置）。这些模式将规定 SELinux 在主体请求时如何应对。这些模式是：

1. Enforcing强制— SELinux 策略强制执行，基于 SELinux 策略规则授予或拒绝主体对目标的访问
2. Permissive宽容— SELinux 策略不强制执行，不实际拒绝访问，但会有拒绝信息写入日志
3. Disabled禁用— 完全禁用 SELinux


# SELinux 策略

SELinux 策略有两种：

1. Targeted目标 — 只有目标网络进程（dhcpd，httpd，named，nscd，ntpd，portmap，snmpd，squid，以及 syslogd）受保护
2. Strict严格 — 对所有进程完全的 SELinux 保护


# 相关命令

```bash
id -Z
ls -Z
```


# Links

* [https://wiki.centos.org/HowTos/SELinux](https://wiki.centos.org/HowTos/SELinux)

