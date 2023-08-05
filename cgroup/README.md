cgroup
===============

* `Namespace` 资源的隔离，名字隔离
* `CGroups` 资源的限制
* `cgroup-v1`
* `cgroup-v2` Cgroup v2 brings exciting new features in areas such as eBPF and rootless containers.


# 查看当前版本

```
grep -w cgroup /proc/filesystems
grep -w cgroup2 /proc/filesystems
```

# Enable CGroup V1

```
dnf install -y grubby
sudo grubby --update-kernel=ALL --args="systemd.unified_cgroup_hierarchy=0"
```

# Enable CGroup V2

```
dnf install -y grubby
sudo grubby --update-kernel=ALL --args="systemd.unified_cgroup_hierarchy=1"
```


# Links

- https://www.kernel.org/doc/html/latest/admin-guide/cgroup-v1/devices.html

