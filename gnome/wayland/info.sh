#!/bin/bash
set -e
wayland-scanner --version
echo WAYLAND_DISPLAY=$WAYLAND_DISPLAY
echo DISPLAY=$DISPLAY
