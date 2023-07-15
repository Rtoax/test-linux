/* This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://www.wtfpl.net/ for more details. */
#include <arpa/inet.h>
#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <xtables.h>
#include <linux/netfilter.h>
#include "xt_ipaddr.h"

static const struct option ipaddr_mt_opts[] = {
	{.name = "ipsrc", .has_arg = true, .val = '1'},
	{.name = "ipdst", .has_arg = true, .val = '2'},
	{NULL},
};

static void ipaddr_mt_help(void)
{
	printf("ipaddr match options:\n"
			"[!] --ipsrc addr    Match source address of packet\n"
			"[!] --ipdst addr    Match destination address of packet\n"
	);
}

static void ipaddr_mt_init(struct xt_entry_match *match)
{
	struct xt_ipaddr_mtinfo *info = (void *)match->data;

	inet_pton(PF_INET, "192.0.2.137", &info->dst.in);
}

static int ipaddr_mt4_parse(int c, char **argv, int invert,
    unsigned int *flags, const void *entry, struct xt_entry_match **match)
{
	struct xt_ipaddr_mtinfo *info = (void *)(*match)->data;
	struct in_addr *addrs, mask;
	unsigned int naddrs;

	switch (c) {
	case '1': /* --ipsrc */
		if (*flags & XT_IPADDR_SRC)
			xtables_error(PARAMETER_PROBLEM, "xt_ipaddr: "
				"Only use \"--ipsrc\" once!");
		*flags |= XT_IPADDR_SRC;
		info->flags |= XT_IPADDR_SRC;
		if (invert)
			info->flags |= XT_IPADDR_SRC_INV;
		xtables_ipparse_any(optarg, &addrs, &mask, &naddrs);
		if (naddrs != 1)
			xtables_error(PARAMETER_PROBLEM, "%s does not resolve to exactly "
				"one address", optarg);
		memcpy(&info->src.in, addrs, sizeof(*addrs));
		return true;


	case '2': /* --ipdst */
		if (*flags & XT_IPADDR_DST)
			xtables_error(PARAMETER_PROBLEM, "xt_ipaddr: "
				"Only use \"--ipdst\" once!");
		*flags |= XT_IPADDR_DST;
		info->flags |= XT_IPADDR_DST;
		if (invert)
			info->flags |= XT_IPADDR_DST_INV;
		addrs = xtables_numeric_to_ipaddr(optarg);
		if (addrs == NULL)
			xtables_error(PARAMETER_PROBLEM, "xt_ipaddr: "
				"Parse error at %s\n", optarg);
		memcpy(&info->dst.in, addrs, sizeof(*addrs));
		return true;
	}

	return false;
}

static int ipaddr_mt6_parse(int c, char **argv, int invert,
    unsigned int *flags, const void *entry, struct xt_entry_match **match)
{
	struct xt_ipaddr_mtinfo *info = (void *)(*match)->data;
	struct in6_addr *addrs;

	switch (c) {
	case '1': /* --ipsrc */
		if (*flags & XT_IPADDR_SRC)
			xtables_error(PARAMETER_PROBLEM, "xt_ipaddr: "
				"Only use \"--ipsrc\" once!");
		*flags |= XT_IPADDR_SRC;
		info->flags |= XT_IPADDR_SRC;
		if (invert)
			info->flags |= XT_IPADDR_SRC_INV;
		addrs = xtables_numeric_to_ip6addr(optarg);
		if (addrs == NULL)
			xtables_error(PARAMETER_PROBLEM, "xt_ipaddr: "
				"Parse error at %s", optarg);
		memcpy(&info->src.in6, addrs, sizeof(*addrs));
		return true;

	case '2': /* --ipdst */
		if (*flags & XT_IPADDR_DST)
			xtables_error(PARAMETER_PROBLEM, "xt_ipaddr: "
				"Only use \"--ipdst\" once!");
		*flags |= XT_IPADDR_DST;
		info->flags |= XT_IPADDR_DST;
		if (invert)
			info->flags |= XT_IPADDR_DST_INV;
		addrs = xtables_numeric_to_ip6addr(optarg);
		if (addrs == NULL)
			xtables_error(PARAMETER_PROBLEM, "xt_ipaddr: "
				"Parse error at %s", optarg);
		memcpy(&info->dst.in6, addrs, sizeof(*addrs));
		return true;
	}

	return false;
}

static void ipaddr_mt_check(unsigned int flags)
{
	if (flags == 0)
		xtables_error(PARAMETER_PROBLEM, "xt_ipaddr: You need to "
			"specify at least \"--ipsrc\" or \"--ipdst\".");
}

static void ipaddr_mt4_print(const void *entry,
    const struct xt_entry_match *match, int numeric)
{
	const struct xt_ipaddr_mtinfo *info = (const void *)match->data;

	if (info->flags & XT_IPADDR_SRC) {
		printf("src IP ");
		if (info->flags & XT_IPADDR_SRC_INV)
			printf("! ");
		printf("%s ", numeric ?
		       xtables_ipaddr_to_numeric(&info->src.in) :
		       xtables_ipaddr_to_anyname(&info->src.in));
	}

	if (info->flags & XT_IPADDR_DST) {
		printf("dst IP ");
		if (info->flags & XT_IPADDR_DST_INV)
			printf("! ");
		printf("%s ", numeric ?
		       xtables_ipaddr_to_numeric(&info->dst.in) :
		       xtables_ipaddr_to_anyname(&info->dst.in));
	}
}

static void ipaddr_mt6_print(const void *entry,
    const struct xt_entry_match *match, int numeric)
{
	const struct xt_ipaddr_mtinfo *info = (const void *)match->data;

	if (info->flags & XT_IPADDR_SRC) {
		printf("src IP ");
		if (info->flags & XT_IPADDR_SRC_INV)
			printf("! ");
		printf("%s ", numeric ?
		       xtables_ip6addr_to_numeric(&info->src.in6) :
		       xtables_ip6addr_to_anyname(&info->src.in6));
	}

	if (info->flags & XT_IPADDR_DST) {
		printf("dst IP ");
		if (info->flags & XT_IPADDR_DST_INV)
			printf("! ");
		printf("%s ", numeric ?
		       xtables_ip6addr_to_numeric(&info->dst.in6) :
		       xtables_ip6addr_to_anyname(&info->dst.in6));
	}
}

static void ipaddr_mt4_save(const void *entry,
    const struct xt_entry_match *match)
{
	const struct xt_ipaddr_mtinfo *info = (const void *)match->data;

	if (info->flags & XT_IPADDR_SRC) {
		if (info->flags & XT_IPADDR_SRC_INV)
			printf("! ");
		printf("--ipsrc %s ",
		       xtables_ipaddr_to_numeric(&info->src.in));
	}

	if (info->flags & XT_IPADDR_DST) {
		if (info->flags & XT_IPADDR_DST_INV)
			printf("! ");
		printf("--ipdst %s ",
		        xtables_ipaddr_to_numeric(&info->dst.in));
	}
}

static void ipaddr_mt6_save(const void *entry,
    const struct xt_entry_match *match)
{
	const struct xt_ipaddr_mtinfo *info = (const void *)match->data;

	if (info->flags & XT_IPADDR_SRC) {
		if (info->flags & XT_IPADDR_SRC_INV)
			printf("! ");
		printf("--ipsrc %s ",
		       xtables_ip6addr_to_numeric(&info->src.in6));
	}

	if (info->flags & XT_IPADDR_DST) {
		if (info->flags & XT_IPADDR_DST_INV)
			printf("! ");
		printf("--ipdst %s ",
		       xtables_ip6addr_to_numeric(&info->dst.in6));
	}
}

static struct xtables_match ipaddr_mt_reg = {
	.version       = XTABLES_VERSION,
	.name          = "ipaddr",
	.revision      = 0,
	.family        = PF_INET,
	.size          = XT_ALIGN(sizeof(struct xt_ipaddr_mtinfo)),
	.userspacesize = XT_ALIGN(sizeof(struct xt_ipaddr_mtinfo)),
	/* called when user execs "iptables -m ipaddr -h" */
	.help          = ipaddr_mt_help,
	/* populates the xt_ipaddr_mtinfo before parse (eg. to set defaults). */
	.init          = ipaddr_mt_init,
	/* called when user enters new rule; it validates the args (--ipsrc). */
	.parse         = ipaddr_mt4_parse,
	/* last chance for sanity checks after parse. */
	.final_check   = ipaddr_mt_check,
	/* called when user execs "iptables -L" */
	.print         = ipaddr_mt4_print,
	/* called when user execs "iptables-save" */
	.save          = ipaddr_mt4_save,
	.extra_opts    = ipaddr_mt_opts,
};

static struct xtables_match ipaddr_mt6_reg = {
	.version       = XTABLES_VERSION,
	.name          = "ipaddr",
	.revision      = 0,
	.family        = PF_INET6,
	.size          = XT_ALIGN(sizeof(struct xt_ipaddr_mtinfo)),
	.userspacesize = XT_ALIGN(sizeof(struct xt_ipaddr_mtinfo)),
	.help          = ipaddr_mt_help,
	.init          = ipaddr_mt_init,
	.parse         = ipaddr_mt6_parse,
	.final_check   = ipaddr_mt_check,
	.print         = ipaddr_mt6_print,
	.save          = ipaddr_mt6_save,
	.extra_opts    = ipaddr_mt_opts,
};

static void _init(void)
{
	xtables_register_match(&ipaddr_mt_reg);
	xtables_register_match(&ipaddr_mt6_reg);
}
