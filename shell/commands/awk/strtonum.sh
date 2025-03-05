#!/bin/bash

readelf --syms --wide /usr/bin/ls \
	| awk -v type=FUNC '
	{
		if ($4 == type) {
			if (strtonum(0x$2) == 0x0) {
				print $(1)
			}
		}
	}'
