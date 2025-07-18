#!/bin/bash
set -e

desktop_info() {
	echo DISPLAY=$DISPLAY XAUTHORITY=$XAUTHORITY
	echo XDG_CURRENT_DESKTOP=$XDG_CURRENT_DESKTOP
	echo WAYLAND_DISPLAY=$WAYLAND_DISPLAY
	loginctl show-session 1 -p Type
}

desktop_info
