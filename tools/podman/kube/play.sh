#!/bin/bash
set -e

sudo podman kube play fedora.yaml

# Do something...
sudo podman ps --all

# or sudo podman kube play --down fedora.yaml
sudo podman kube down fedora.yaml
