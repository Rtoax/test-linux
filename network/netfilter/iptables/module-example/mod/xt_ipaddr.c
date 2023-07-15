/* This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://www.wtfpl.net/ for more details. */
#include <linux/ip.h>
#include <linux/ipv6.h>
#include <linux/module.h>
#include <linux/version.h>
#include <linux/netfilter.h>
#include <linux/netfilter/x_tables.h>
#include <net/ipv6.h>
#include "xt_ipaddr.h"

#if LINUX_VERSION_CODE < KERNEL_VERSION(4, 10, 0)

/*
 * Until kernel 4.9, the incoming and outgoing devices were par->in and
 * par->out.
 * Starting from kernel 4.10, the devices are par->state->in and
 * par->state->out. However, xt_in() and xt_out() are provided as a future-proof
 * means to access them.
 *
 * So we'll define the equivalent of these functions for older kernels so we
 * can use an unified API.
 */

static inline const struct net_device *xt_in(const struct xt_action_param *par)
{
	return par->in;
}

static inline const struct net_device *xt_out(const struct xt_action_param *par)
{
	return par->out;
}

#endif

static bool ipaddr_mt4(const struct sk_buff *skb, struct xt_action_param *par)
{
	const struct xt_ipaddr_mtinfo *info = par->matchinfo;
	const struct iphdr *iph = ip_hdr(skb);

	printk(KERN_INFO
			"xt_ipaddr: IN=%s OUT=%s SRC=%pI4 DST=%pI4 IPSRC=%pI4 IPDST=%pI4\n",
			(xt_in(par) != NULL) ? xt_in(par)->name : "",
			(xt_out(par) != NULL) ? xt_out(par)->name : "",
			&iph->saddr, &iph->daddr, &info->src, &info->dst);

	if (info->flags & XT_IPADDR_SRC) {
		if ((iph->saddr != info->src.ip)
				^ !!(info->flags & XT_IPADDR_SRC_INV)) {
			printk(KERN_NOTICE "src IP - no match\n");
			return false;
		}
	}

	if (info->flags & XT_IPADDR_DST) {
		if ((iph->daddr != info->dst.ip)
				^ !!(info->flags & XT_IPADDR_DST_INV)) {
			printk(KERN_NOTICE "dst IP - no match\n");
			return false;
		}
	}

	return true;
}

static bool ipaddr_mt6(const struct sk_buff *skb, struct xt_action_param *par)
{
	const struct xt_ipaddr_mtinfo *info = par->matchinfo;
	const struct ipv6hdr *iph = ipv6_hdr(skb);

	printk(KERN_INFO
			"xt_ipaddr: IN=%s OUT=%s SRC=%pI6c DST=%pI6c IPSRC=%pI6c IPDST=%pI6c\n",
			(xt_in(par) != NULL) ? xt_in(par)->name : "",
			(xt_out(par) != NULL) ? xt_out(par)->name : "",
			&iph->saddr, &iph->daddr, &info->src.in6, &info->dst.in6);

	if (info->flags & XT_IPADDR_SRC) {
		if ((ipv6_addr_cmp(&iph->saddr, &info->src.in6) != 0)
				^ !!(info->flags & XT_IPADDR_SRC_INV)) {
			printk(KERN_NOTICE "src IP - no match\n");
			return false;
		}
	}

	if (info->flags & XT_IPADDR_DST) {
		if ((ipv6_addr_cmp(&iph->daddr, &info->dst.in6) != 0)
				^ !!(info->flags & XT_IPADDR_DST_INV)) {
			printk(KERN_NOTICE "dst IP - no match\n");
			return false;
		}
	}

	return true;
}

static int ipaddr_mt_check(const struct xt_mtchk_param *par)
{
	const struct xt_ipaddr_mtinfo *info = par->matchinfo;

	printk(KERN_INFO "xt_ipaddr: Added a rule with -m ipaddr in "
			"the %s table; this rule is reachable through hooks 0x%x\n",
			par->table, par->hook_mask);

	if (par->match->family == NFPROTO_IPV4
			&& ntohl(info->src.ip) == 0xDEADBEEF) {
		printk(KERN_INFO "xt_ipaddr: I just thought I do not want "
				"to let you match on 222.173.190.239\n");
		return -EPERM;
	}

	return 0;
}

static void ipaddr_mt_destroy(const struct xt_mtdtor_param *par)
{
	printk(KERN_INFO "One rule with ipaddr match got deleted\n");
}

static struct xt_match ipaddr_mt_reg[] __read_mostly = {
	{
		.name       = "ipaddr",
		.revision   = 0,
		.family     = NFPROTO_IPV4,
		.match      = ipaddr_mt4,
		.checkentry = ipaddr_mt_check,
		.destroy    = ipaddr_mt_destroy,
		.matchsize  = XT_ALIGN(sizeof(struct xt_ipaddr_mtinfo)),
		.me         = THIS_MODULE,
	},
	{
		.name       = "ipaddr",
		.revision   = 0,
		.family     = NFPROTO_IPV6,
		.match      = ipaddr_mt6,
		.checkentry = ipaddr_mt_check,
		.destroy    = ipaddr_mt_destroy,
		.matchsize  = XT_ALIGN(sizeof(struct xt_ipaddr_mtinfo)),
		.me         = THIS_MODULE,
	},
};

static int __init ipaddr_mt_init(void)
{
	return xt_register_matches(ipaddr_mt_reg, ARRAY_SIZE(ipaddr_mt_reg));
}

static void __exit ipaddr_mt_exit(void)
{
	xt_unregister_matches(ipaddr_mt_reg, ARRAY_SIZE(ipaddr_mt_reg));
}

module_init(ipaddr_mt_init);
module_exit(ipaddr_mt_exit);
MODULE_DESCRIPTION("Xtables: Match source/destination address");
MODULE_LICENSE("GPL");
MODULE_ALIAS("ipt_ipaddr");
MODULE_ALIAS("ip6t_ipaddr");
