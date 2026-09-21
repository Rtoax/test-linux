#!/bin/bash
set -e

modules_x86_64=( 9p 9pnet 9pnet_virtio af_alg af_packet_diag algif_hash ansi_cprng arptable_filter arp_tables arpt_mangle binfmt_misc brd bridge ext4 failover fuse ip_set ip_set_bitmap_ip ip_set_bitmap_ipmac ip_set_bitmap_port ip_set_hash_ip ip_set_hash_ipmark ip_set_hash_ipport ip_set_hash_ipportip ip_set_hash_ipportnet ip_set_hash_mac ip_set_hash_net ip_set_hash_netiface ip_set_hash_netnet ip_set_hash_netport ip_set_hash_netportnet ip_set_list_set iptable_filter iptable_mangle iptable_nat iptable_raw iptable_security ipt_ah ipt_ECN ipt_REJECT ipt_rpfilter ipt_SYNPROXY ip_vs ip_vs_dh ip_vs_fo ip_vs_ftp ip_vs_lblc ip_vs_lblcr ip_vs_lc ip_vs_nq ip_vs_ovf ip_vs_pe_sip ip_vs_rr ip_vs_sed ip_vs_sh ip_vs_wlc ip_vs_wrr irqbypass jbd2 libnvdimm llc loop mbcache nd_btt nd_pmem net_failover nf_conncount nf_conntrack nf_conntrack_amanda nf_conntrack_broadcast nf_conntrack_ftp nf_conntrack_h323 nf_conntrack_irc nf_conntrack_netbios_ns nf_conntrack_netlink nf_conntrack_pptp nf_conntrack_sane nf_conntrack_sip nf_conntrack_snmp nf_conntrack_tftp nf_defrag_ipv4 nf_defrag_ipv6 nf_dup_ipv4 nf_dup_ipv6 nfit nf_nat nf_nat_amanda nf_nat_ftp nf_nat_h323 nf_nat_irc nf_nat_pptp nf_nat_sip nf_nat_snmp_basic nf_nat_tftp nfnetlink nfnetlink_acct nfnetlink_cthelper nfnetlink_cttimeout nfnetlink_log nfnetlink_osf nfnetlink_queue nf_reject_ipv4 nf_synproxy_core nf_tproxy_ipv4 overlay ptp_kvm sch_fq sch_multiq sd_mod stp tcp_bbr ts_bm ts_fsm ts_kmp veth vfio vfio_iommu_type1 vfio-pci virqfd virtio_blk virtio_console virtio_net virtio_scsi vmw_vsock_virtio_transport vmw_vsock_virtio_transport_common vsock xfs xt_addrtype xt_bpf xt_cgroup xt_CHECKSUM xt_CLASSIFY xt_cluster xt_comment xt_connbytes xt_connlabel xt_connlimit xt_connmark xt_conntrack xt_cpu xt_CT xt_dccp xt_devgroup xt_dscp xt_DSCP xt_ecn xt_esp xt_hashlimit xt_helper xt_hl xt_HL xt_HMARK xt_IDLETIMER xt_ipcomp xt_iprange xt_ipvs xt_l2tp xt_length xt_limit xt_LOG xt_mac xt_mark xt_MASQUERADE xt_multiport xt_nat xt_NETMAP xt_nfacct xt_NFLOG xt_NFQUEUE xt_osf xt_owner xt_pkttype xt_policy xt_quota xt_rateest xt_RATEEST xt_realm xt_recent xt_REDIRECT xt_sctp xt_set xt_state xt_statistic xt_string xt_tcpmss xt_TCPMSS xt_TCPOPTSTRIP xt_TEE xt_time xt_TPROXY xt_TRACE xt_u32 )

if [[ $(uname -m) == x86_64 ]]; then
	modules=( ${modules_x86_64[@]} )
else
	log "Not support $(uname -m) yet"
	exit 1
fi

log() {
	echo "KATA: $@"
}

log "starting..."

log "mount /proc"
mount -t proc proc /proc

log "show informations"
ls /proc

log "loading kernel modules"
for m in ${modules[@]}
do
	log "modprobe $m"
	/usr/sbin/modprobe $m || {
		log "modprobe $m failed" || true
	}
done

log "starting kata-agent"
/sbin/kata-agent --help
exec /sbin/kata-agent "$@"
