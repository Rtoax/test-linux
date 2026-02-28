#!/bin/bash
set -e

if [[ -d /usr/share/anaconda ]]; then
	ls /usr/share/anaconda/{dbus,ui/hubs,ui/spokes}
fi
