virt2phy:
	$(Q)make -C ../../mm/ virt2phy
	$(Q)rm -f virt2phy
	$(Q)cp ../../mm/virt2phy .

post-nvdso:
	$(Q)${NVDSO_ENV} LD_PRELOAD=./libnvdso.so ./main

clean-nvdso:
	$(Q)rm -f *.out vdso.elf virt2phy
