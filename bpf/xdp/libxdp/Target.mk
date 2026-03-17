include bpf/xdp.mk

${OUTPUT}xsk_user.o: ${OUTPUT}xdp_xsk.skel.h

.PHONY: post-xdp_elfsec
post-xdp_elfsec:
	${Q}$(call attach_xdp_with_ip,lo,${OUTPUT}xdp_elfsec.bpf.o,mysection)
	${Q}$(call detach_xdp_with_ip,lo)

.PHONY: post-xdp_drop
post-xdp_drop:
	${Q}$(call attach_xdp,lo,${OUTPUT}xdp_drop.bpf.o,drop)
	${Q}$(call detach_xdp,lo,drop)
