#!/bin/bash
set -e

sudo podman kube play --start fedora.yaml

# Do something...
sudo podman ps --all --format "table {{.Names}}\t{{.Image}}"

# or sudo podman kube play --down fedora.yaml
sudo podman kube down fedora.yaml
