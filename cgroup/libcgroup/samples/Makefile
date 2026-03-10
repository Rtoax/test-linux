include libcgroup.mk

target-y += cgroup_version
target-y += cgroup_get_subsys_mount_point
target-y += cgroup_new_cgroup

CFLAGS += ${libcgroup-cflags}
LDFLAGS += ${libcgroup-ldflags}

include main.mk
