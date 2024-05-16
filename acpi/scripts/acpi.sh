#!/bin/bash
set -e

sudo acpidump > acpidump.dat
sudo acpixtract -a acpidump.dat

if [[ -e pptt.dat ]]; then
	iasl -d pptt.dat
fi

for f in $(ls *.dat)
do
	iasl -d $f
done

