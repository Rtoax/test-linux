sub-dir := tcg/samples/
sub-dir += qcow2

TARGETS_TEST := test0
TARGETS_CLEAN := clean0

include ../template/main.mk

test0:
	${Q}$(SHELL) support-cpu.sh
	${Q}$(SHELL) libqemu_examples.sh

clean0:
	${Q}rm -f *.qcow2 *.raw
