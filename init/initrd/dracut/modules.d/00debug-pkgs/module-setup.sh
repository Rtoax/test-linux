#!/bin/bash
# Add some utils into initrd/initramfs.

# called by dracut
check() {
	return 0
}

# called by dracut
depends() {
	echo network
	echo systemd
	return 0
}

IPTABLES_MODULES="ip6_tables ip6table_nat ip_tables iptable_filter iptable_nat nf_conntrack nf_defrag_ipv4 nf_defrag_ipv6 nf_nat xt_MASQUERADE xt_comment xt_conntrack"

# called by dracut
installkernel() {
	# for raid and crypt support, the kernel module is needed unconditionally, even in hostonly mode
	hostonly='' instmods br_netfilter $IPTABLES_MODULES dm_crypt =crypto
}

get_pkg_deps() {
	deps=$(rpm -q --requires "$@" | while read req ver; do
		p=$(rpm -q --whatprovides "$req")
		[ $? -eq 0 ] && echo $p
	done | sort -u)
	echo "$@ $deps"
}

debug_reqs() {
	packages=$(get_pkg_deps util-linux tcpdump ethtool iputils iproute)
	for p in $packages; do
		rpm -ql $p | grep -E -v "(/man/)|(/bash-completion/)|(/doc/)" | sed -e 's/\n/ /g'
	done | sort -u
}

# called by dracut
install() {
	inst_multiple -o $(debug_reqs)
}
