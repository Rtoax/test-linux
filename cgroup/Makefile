include ../kconfig.mk

sub-dir := libcgroup
sub-dir += tools

targets-post := info
targets-clean := info_clean

include ../template/main.mk

info:
	$(Q)./info.sh > info.sh.log
info_clean:
	${Q}rm -f info.sh.log
