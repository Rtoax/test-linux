// SPDX-License-Identifier: GPL-3.0
#include <stdio.h>
#include <linux/icmp.h>

#include "icmp_helpers.h"

const char *stricmptype(uint8_t type)
{
	switch (type) {
#define CASE(v) case ICMP_##v: return (#v);
	CASE(ECHOREPLY);
	CASE(DEST_UNREACH);
	CASE(SOURCE_QUENCH);
	CASE(REDIRECT);
	CASE(ECHO);
	CASE(TIME_EXCEEDED);
	CASE(PARAMETERPROB);
	CASE(TIMESTAMP);
	CASE(TIMESTAMPREPLY);
	CASE(INFO_REQUEST);
	CASE(INFO_REPLY);
	CASE(ADDRESS);
	CASE(ADDRESSREPLY);
	}
	return "Unknown";
}
