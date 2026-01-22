include libcgroup.mk

target-y :=
target-y += cgroup_version
target-y += cgroup_get_subsys_mount_point
target-y += cgroup_new_cgroup

CFLAGS += ${libcgroup-cflags}
LDFLAGS += ${libcgroup-ldflags}

include main.mk

cgroup_version: cgroup_version.o
cgroup_get_subsys_mount_point: cgroup_get_subsys_mount_point.o
cgroup_new_cgroup: cgroup_new_cgroup.o
