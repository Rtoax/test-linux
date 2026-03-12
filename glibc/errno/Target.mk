nr_errno.o: nr_errno.h

nr_errno.h: errno.sh
	$(shell bash errno.sh)

clean-more:
	${Q}rm -f nr_errno.h
