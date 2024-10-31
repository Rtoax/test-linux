cgroup freezer
===============

- `CONFIG_CGROUP_FREEZER`


# Usage

```
# mkdir /sys/fs/cgroup/freezer
# mount -t cgroup -ofreezer freezer /sys/fs/cgroup/freezer
# mkdir /sys/fs/cgroup/freezer/0
# echo $some_pid > /sys/fs/cgroup/freezer/0/tasks

# cat /sys/fs/cgroup/freezer/0/freezer.state
THAWED

# echo FROZEN > /sys/fs/cgroup/freezer/0/freezer.state
# cat /sys/fs/cgroup/freezer/0/freezer.state
FREEZING
# cat /sys/fs/cgroup/freezer/0/freezer.state
FROZEN

# echo THAWED > /sys/fs/cgroup/freezer/0/freezer.state
# cat /sys/fs/cgroup/freezer/0/freezer.state
THAWED
```

# Links

- https://www.kernel.org/doc/html/latest/admin-guide/cgroup-v1/freezer-subsystem.html

