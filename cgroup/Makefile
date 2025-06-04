include ../kconfig.mk

sub-dir := libcgroup
sub-dir += tools

TARGETS_POST := info
TARGETS_CLEAN := info_clean

include ../template/main.mk

info:
	$(Q)./info.sh > info.sh.log
info_clean:
	${Q}rm -f info.sh.log
