kernel:
	${Q}make -C ${KERNELDIR} M=$(PWD) modules
