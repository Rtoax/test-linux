target-prep-y := helloworld.dtb

include ../../../template/main.mk

%.dtb: %.dts
	$(call log_tgt_exe,DTC,$(<),$(@))
	$(Q)dtc -I dts -O dtb -o $(@) $(<) --include ${PWD}
