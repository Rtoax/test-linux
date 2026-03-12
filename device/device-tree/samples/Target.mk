%.dtb: %.dts
	$(call log_tgt,DTC,$(@))
	$(Q)dtc -I dts -O dtb -o $(@) $(<) --include ${PWD}
