include bpf/xdp.mk

${OUTPUT}xsk_user.o: ${OUTPUT}xdp_xsk.skel.h

.PHONY: post-xdp_elfsec
post-xdp_elfsec:
	${Q}$(call attach_xdp_with_ip,lo,${OUTPUT}xdp_elfsec.bpf.o,mysection)
	${Q}$(call detach_xdp_with_ip,lo)
