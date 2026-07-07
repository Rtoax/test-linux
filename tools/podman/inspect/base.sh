#!/bin/bash
set -e

for id in $(sudo podman ps --format "{{.ID}}")
do
	name=$(sudo podman inspect ${id} --format "{{ .Name }}")
	image=$(sudo podman inspect ${id} --format "{{ .ImageName }}")
	printf "%-16s\t%s\n" ${name} ${image}
done
