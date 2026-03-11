#!/bin/bash
set -e

./sigpending &
sleep 1
kill -2 $(pidof sigpending) # SIGINT
sleep 1
kill -20 $(pidof sigpending) # SIGTSTP
sleep 1
kill -9 $(pidof sigpending)
