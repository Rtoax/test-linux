#!/bin/bash
set -e

image=fedora
[[ $# -gt 0 ]] && image=$1

sudo podman manifest inspect ${image} | jq '.manifests[].platform.architecture'
