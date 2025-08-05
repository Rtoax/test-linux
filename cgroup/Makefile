include ../kconfig.mk

sub-dir := libcgroup
sub-dir += tools

targets := cgroup_examples

targets-post := info
targets-clean := info_clean

include ../template/main.mk

cgroup_helpers.o: cgroup_helpers.h
cgroup_examples.o: cgroup_helpers.h
cgroup_examples: cgroup_examples.o cgroup_helpers.o

info:
	$(Q)./info.sh > info.sh.log
info_clean:
	${Q}rm -f info.sh.log
