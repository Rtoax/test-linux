$(info INFO: This is info)
$(warning WARNING: This is warning)
#$(error ERROR: This error)

all:
	make -f Makefile.user
	make -f Makefile.kernel
clean:
	make clean -f Makefile.user
	make clean -f Makefile.kernel
