include make.mk

virt2phy:
	$(Q)${MAKE} -C ../../mm/ virt2phy
	$(Q)cp ../../mm/virt2phy .

post-nvdso:
	$(Q)./main
	$(Q)${NVDSO_ENV} LD_PRELOAD=./libnvdso.so ./main

clean-nvdso:
	$(Q)rm -f *.out vdso.elf virt2phy
