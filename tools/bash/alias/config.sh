#!/bin/bash

if [[ $(uname -m) == myarch ]]; then
	MY_ARCH=myarch
else
	MY_ARCH=$(arch)
fi
