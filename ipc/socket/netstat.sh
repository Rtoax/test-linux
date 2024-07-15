#!/bin/bash

netstat_unix() {
	sudo netstat --protocol=unix --program
}

netstat_unix | sed 's/^/UNIX: /g'

ss_unix() {
	sudo ss --unix
}

ss_unix | sed 's/^/UNIX: /g'
