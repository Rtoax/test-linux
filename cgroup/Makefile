include cgroup.mk
include kconfig.mk
include libcgroup.mk

subdir-${HAVE_LIBCGROUP} += libcgroup
subdir-y += tools
subdir-${CGROUP_V1} += v1
subdir-${CGROUP_V2} += v2

target-y := cgroup_examples

cgroup_examples-objs := cgroup_helpers.o

target-prog-y := info.sh

include main.mk
