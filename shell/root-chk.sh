#!/bin/bash

[[  ROOT::PERMISSION ]]

check() {
	echo "check ROOT::PERMISSION"
	[[ $UID -ne 0 ]] && {
		echo -e  "require root user"
	}
	true
}
check
