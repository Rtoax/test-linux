clean0:
	$(Q)rm -f hello.no-debug hello.debug hello.orig

%.dwz: %
	@$(call log_tgt,DWZ,$(@))
	${Q}cp $(<) $(<).orig
	${Q}dwz $(<) -o $(<).dwz

%.strip: %
	@$(call log_tgt,STRIP,$(@))
	${Q}strip --strip-debug $(<) -o $(<).no-debug
	${Q}eu-strip $(<) -f $(<).debug -o $(<).strip
	${Q}objcopy --strip-debug $(<) $(<).strip2
