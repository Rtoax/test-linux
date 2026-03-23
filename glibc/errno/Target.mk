${OUTPUT}nr_errno.o: errors.h

errors.h: errno.sh
	$(shell bash errno.sh)

clean-more:
	${Q}rm -f errors.h
