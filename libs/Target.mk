post1:
	$(call log_tgt,TEST,$(@))
	${Q}LD_LIBRARY_PATH=$(shell pwd) ./byteswap
	${Q}clear
	${Q}./gotoxy
	${Q}clear
	${Q}./file.sh test
