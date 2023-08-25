#!/bin/bash

make
sudo ./fanotify  &
sleep 0.5
cat /etc/os-release
