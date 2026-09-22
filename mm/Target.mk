include make.mk

numa.a.1:
	$(Q)${MAKE} -C ../numa numa.a
	$(Q)cp ../numa/numa.a numa.a.1

numa.so:
	$(Q)${MAKE} -C ../numa numa.so
	$(Q)cp ../numa/numa.so numa.so
