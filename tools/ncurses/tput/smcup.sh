#!/bin/bash
set -e

tput smcup # swap to a clean screen
tput init

cat /etc/os-release
sleep 0.5

tput cnorm
tput rmcup # turn off screen, back to main screen
