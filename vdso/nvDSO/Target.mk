virt2phy:
	$(Q)pushd ../../mm/; make virt2phy; popd
	$(Q)cp ../../mm/virt2phy .

post-nvdso:
	$(Q)${NVDSO_ENV} LD_PRELOAD=./libnvdso.so ./main

clean-nvdso:
	$(Q)rm -f *.out vdso.elf virt2phy
