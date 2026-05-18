#!/bin/bash
set -e

sudo podman run --rm -td --name fedora registry.fedoraproject.org/fedora:44 bash
sudo podman generate kube fedora
sudo podman rm --force fedora
