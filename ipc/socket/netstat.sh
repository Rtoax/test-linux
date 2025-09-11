#!/bin/bash

stat_port()
{
	netstat -anpltu
}

stat_protocol()
{
	# --statistics, -s: Display summary statistics for each protocol.
	netstat -s

	ss -s
}

netstat_unix() {
	sudo netstat --protocol=unix --program
}

netstat_unix | sed 's/^/UNIX: /g'

ss_unix() {
	sudo ss --unix
}

ss_unix | sed 's/^/UNIX: /g'
