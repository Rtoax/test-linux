#!/bin/bash

readelf --syms --wide /usr/bin/ls \
	| awk '
	{
		if (index($8, "get") == 1) {
			print $8", len "length($8)
		}
	}'
