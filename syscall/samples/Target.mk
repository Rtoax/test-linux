nr.h: nr.sh
	$(shell bash nr.sh)

clean0:
	${Q}rm -rf nr.h *.txt testfile tmp-*
