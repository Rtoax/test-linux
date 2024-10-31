cgroup
===============

* `Namespace` 资源的隔离，名字隔离
* `cgroup` 资源的限制 (首字母永远不大写, never capitalized)
	* `cgroup-v1`
	* `cgroup-v2` Cgroup v2 brings exciting new features in areas such as eBPF and rootless containers.


# Mount

```bash
$ sudo mount -t cgroup cgroup /cgroup
$ echo "cgroup /cgroup cgroup defaults 0 0" | sudo tee --append /etc/fstab
```


# Check Current cgroup Version

```
grep -w cgroup /proc/filesystems
grep -w cgroup2 /proc/filesystems
```

# Enable cgroup V1

## Fedora Like OS

```
dnf install -y grubby
sudo grubby --update-kernel=ALL --args="systemd.unified_cgroup_hierarchy=0 systemd.legacy_systemd_cgroup_controller"
sudo systemctl reboot
```

# Enable cgroup V2

## Fedora Like OS

```
dnf install -y grubby
sudo grubby --update-kernel=ALL --args="systemd.unified_cgroup_hierarchy=1"
sudo systemctl reboot
```


# Links

- [[译] Control Group v2（cgroupv2 权威指南）（KernelDoc, 2021）](https://arthurchiao.art/blog/cgroupv2-zh/)
- https://www.kernel.org/doc/html/latest/admin-guide/cgroup-v1/devices.html

