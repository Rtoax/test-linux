#!/bin/bash
set -e

sudo acpidump > acpidump.dat
sudo acpixtract -a acpidump.dat || true

if [[ -e pptt.dat ]]; then
	iasl -d pptt.dat || true
fi

for f in $(ls *.dat)
do
	iasl -d $f || true
done
