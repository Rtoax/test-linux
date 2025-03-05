#!/bin/bash

readelf --syms --wide /usr/bin/ls \
	| awk '
	{
		if (match($8, "get")) {
			print "match GLIBC: "$8
		}
	}'
