#!/bin/bash
# Random mac address

openssl rand -hex 6 | sed -r 's/(..)/\1:/g' | sed 's/.$//'

openssl rand -hex 6 | sed -r 's/(..)(..)(..)(..)(..)(..)/\1:\2:\3:\4:\5:\6/g'

openssl rand -hex 6 | sed -r 's/..\B/&:/g'
