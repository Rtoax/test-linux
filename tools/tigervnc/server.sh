#!/bin/bash
set -e

source /home/rongtao/.profile

sudo -u rongtao tigervncserver -kill :1
sudo -u rongtao tigervncserver -xstartup /usr/bin/gnome-session -geometry 1920x1080 -localhost no :1

