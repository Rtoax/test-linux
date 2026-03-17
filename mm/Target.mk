include make.mk

numa.a.1:
	$(Q)${MAKE} -C ../numa numa.a
	$(Q)cp ../numa/numa.a numa.a.1
