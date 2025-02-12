#!/bin/bash
set -e

sudo_no_need_passwd()
{
	if sudo --non-interactive true 2>/dev/null; then
		echo "User $(whoami) has NOPASSWD sudo permissions"
	else
		echo "User $(whoami) does not have NOPASSWD sudo permissions"
	fi
}

sudo_no_need_passwd
