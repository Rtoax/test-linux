LSM: Linux Security Modules (统一访问安全框架)
==============================================

- `CONFIG_DEFAULT_SECURITY`

* Default: `cap_capable`, ...
* AppArmor: `CONFIG_SECURITY_APPARMOR=y`, Mandatory Access Control (MAC), v2.6.36
* BPF: v5.7
* LoadPin: v4.7
* LockDown: v5.4
* SELinux: v2.6.0
* Smack: v2.6.24
* Tomoyo: v2.6.30
* Yama: ptrace relate, v3.4
* SafeSetID: v5.1
* Integrity Policy Enforcement (IPE)


# Kernel Cmdline

```
GRUB_CMDLINE_LINUX="lsm=lockdown,capability,landlock,yama,apparmor,bpf"
```


# Links

- https://www.kernel.org/doc/html/latest/admin-guide/LSM/index.html
- https://www.kernel.org/doc/html/latest/admin-guide/LSM/apparmor.html
- https://www.kernel.org/doc/html/latest/admin-guide/LSM/ipe.html
