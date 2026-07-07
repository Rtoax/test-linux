#!/bin/bash
set -e

for id in $(sudo podman ps --format "{{.ID}}")
do
	name=$(sudo podman inspect ${id} --format "{{ .Name }}")
	for dir in LowerDir MergedDir UpperDir WorkDir
	do
		echo -n "[${name}] ${dir}: "
		sudo podman inspect ${id} --format "{{ .GraphDriver.Data.${dir} }}"
	done
done
