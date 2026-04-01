#!/bin/bash
# newest-repo: https://github.com/dracut-ng/dracut-ng
# other-repo:
# - https://github.com/dracutdevs/dracut (older)
# - https://web.git.kernel.org/pub/scm/boot/dracut/dracut

sudo dracut --kver $(uname -r) --no-hostonly --verbose --force \
	--install 'insmod rmmod modprobe lspci ndctl cxl' \
	--add-drivers 'cxl_acpi cxl_core cxl_mem cxl_pci cxl_pmem cxl_pmu cxl_port' \
	initramfs-$(uname -r).img
