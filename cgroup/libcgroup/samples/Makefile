targets :=
targets += cgroup_version
targets += cgroup_get_subsys_mount_point
targets += cgroup_new_cgroup

CC := gcc

CFLAGS :=
LDFLAGS += -lcgroup

include ../../../template/main.mk

cgroup_version: cgroup_version.o
cgroup_get_subsys_mount_point: cgroup_get_subsys_mount_point.o
cgroup_new_cgroup: cgroup_new_cgroup.o
