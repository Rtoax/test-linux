#!/bin/bash

set -e

rm testfile

make flock-3

# Holding the flock for seconds
./flock-3 &
# Make sure flock-3 above is running
sleep 0.5

# Resource temporarily unavailable until above flock-3 exit
while ! ./flock-3; do :; done

