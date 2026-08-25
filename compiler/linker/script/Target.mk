default.lds:
	@$(call log_tgt,LDS,$(@))
	${Q}LD=${LD} ./default.lds.sh ${LDS_PIE}
