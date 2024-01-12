#!/bin/bash

stat_unix() {
	sudo netstat --protocol=unix --program
}

stat_unix | sed 's/^/UNIX: /g'
