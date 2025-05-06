#pragma once

#ifndef __unused
#define __unused __attribute__((unused))
#endif

struct os_release {
	struct list_head list;
	char release[20];
	char vender[20];
};

static const char __unused *RELEASE[] = {"CentOS", "Ubuntu", "Fedora", "openEuler"};
static const char __unused *VENDERS[] = {"RedHat", "Canonical", "Redhat", "HuaWei"};

static struct os_release __unused centos = {
	.release = "CentOS",
	.vender = "RedHat"
};

static struct os_release __unused ubuntu = {
	.release = "Ubuntu",
	.vender = "Canonical"
};

static struct os_release __unused fedora = {
	.release = "Fedora",
	.vender = "Redhat"
};

static struct os_release __unused openeuler = {
	.release = "openEuler",
	.vender = "HuaWei"
};
