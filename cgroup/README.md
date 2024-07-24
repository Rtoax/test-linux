cgroup
===============

* `Namespace` 资源的隔离，名字隔离
* `CGroups` 资源的限制
* `cgroup-v1`
* `cgroup-v2` Cgroup v2 brings exciting new features in areas such as eBPF and rootless containers.

# Mount

```bash
# 在使用LXC 之前，必须启用cgroup 文件系统。使用下列命令挂载cgroup 文件系统。
mount -t cgroup cgroup /cgroup

# 向/etc/fstab 添加下列语句，就可以在系统启动时自动挂载cgroup 文件系统
echo "cgroup /cgroup cgroup defaults 0 0" >> /etc/fstab
```

# 查看当前版本

```
grep -w cgroup /proc/filesystems
grep -w cgroup2 /proc/filesystems
```

# Enable CGroup V1

```
dnf install -y grubby
sudo grubby --update-kernel=ALL --args="systemd.unified_cgroup_hierarchy=0 systemd.legacy_systemd_cgroup_controller"
sudo systemctl reboot
```

# Enable CGroup V2

```
dnf install -y grubby
sudo grubby --update-kernel=ALL --args="systemd.unified_cgroup_hierarchy=1"
sudo systemctl reboot
```


# Links

- https://www.kernel.org/doc/html/latest/admin-guide/cgroup-v1/devices.html

