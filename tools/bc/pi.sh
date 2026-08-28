#!/bin/bash
set -e
echo "scale=10;4*a(1)" | bc -l -q
