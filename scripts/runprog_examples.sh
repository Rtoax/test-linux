#!/bin/bash
set -e

./runprog.sh -v
./runprog.sh -- runprog.sh -h
./runprog.sh -- /usr/bin/ls
{
	touch ls
	./runprog.sh -- ls
	rm ls
}
