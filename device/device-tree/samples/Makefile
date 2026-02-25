target-prep-y := helloworld.dtb

include main.mk

%.dtb: %.dts
	$(call log_tgt,DTC,$(@))
	$(Q)dtc -I dts -O dtb -o $(@) $(<) --include ${PWD}
