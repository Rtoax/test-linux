relocs-gen.h:
	@$(call log_tgt,HDR,$(@))
	${Q}./relocs.h.sh
