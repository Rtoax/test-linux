include bpf/btf.mk

.PHONY: post0
post0:
	$(Q)./tcpdump.sh
	$(call logo_bpf_summit_2021)
	$(call logo_bpf_summit_2021_nocolor)

${OUTPUT}tcpdump.bpf.o: ${VMLINUX_H}
