#!/bin/bash
set -e

desktop_info() {
	echo DISPLAY=$DISPLAY XAUTHORITY=$XAUTHORITY
	echo $XDG_CURRENT_DESKTOP
}

desktop_info
