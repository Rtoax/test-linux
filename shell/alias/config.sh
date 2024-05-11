#!/bin/bash

if [[ $(uname -m) == myarch ]]; then
	OSTOOLS_ARCH=myarch
else
	OSTOOLS_ARCH=$(arch)
fi
