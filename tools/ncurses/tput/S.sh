#!/bin/bash
set -e

tput smcup

printf '%b' "$(tput -S <<EOF
cup 10 20
bold
setaf 2
EOF
)"
echo "Green screen"
cat /etc/os-release
sleep 0.5

tput rmcup
