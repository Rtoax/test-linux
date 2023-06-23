CGroup V1
=========


# Enable CGroup V1

```
# dnf install -y grubby && \
  sudo grubby \
  --update-kernel=ALL \
  --args="systemd.unified_cgroup_hierarchy=0"
```


# Links

- https://www.kernel.org/doc/html/latest/admin-guide/cgroup-v1/devices.html

