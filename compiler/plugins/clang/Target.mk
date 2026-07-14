${SRCS}:
	@$(call log_tgt,COPY,$(@))
	${Q}cp ${clang-codes} $(shell pwd)
