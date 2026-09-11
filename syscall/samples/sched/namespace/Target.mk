.PHONY: post0
post0:
	${Q}sudo timeout --signal=SIGINT 4 ./fork-ENOMEM.sh test3 || true
