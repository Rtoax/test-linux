test1:
	$(call log_tgt,TEST,$(@))
	${Q}LD_LIBRARY_PATH=$(shell pwd) ./byte
	${Q}clear
	${Q}./gotoxy
	${Q}clear
	${Q}./file.sh test
