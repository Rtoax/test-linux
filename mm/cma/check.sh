#!/bin/bash

. /boot/config-$(uname -r)

if [[ $CONFIG_CMA = y ]]; then
	echo "Support CMA"
else
	echo "Not support CMA"
fi
