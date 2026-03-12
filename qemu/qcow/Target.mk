include qcow2.mk

%.qcow2:
	$(call log_tgt,QCOW2,$(@))
	$(call create_qcow2,$(@),1G)

post-qcow2: ${QCOW2S}
	$(call log_tgt,TEST,$(@))
	${Q}./qcow2 -q a.qcow2 --verbose
