subdir-y := tcg/samples/
subdir-y += qcow2

target-test-y := test0
target-clean-y := clean0

include ../template/main.mk

test0:
	${Q}$(SHELL) support-cpu.sh
	${Q}$(SHELL) libqemu_examples.sh

clean0:
	${Q}rm -f *.qcow2 *.raw
