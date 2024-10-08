#!/bin/bash

cat /etc/os-release | tr '=' ' ' \
| awk '
	{
		if ($1 == "ID") {
			gsub("centos", "CENTOS");
			gsub("fedora", "FEDORA");
			print
		} else {
			print $0
		}
	}
'
