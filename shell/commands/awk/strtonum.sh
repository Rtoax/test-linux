#!/bin/bash
set -e

readelf --syms --wide /usr/bin/ls \
	| awk -v type=FUNC '
	{
		if ($4 == type) {
			if (strtonum("0x"$2) == 0x0) {
				printf $(1)","
			}
		}
	}
	END {
		printf "\n"
	}
	'
