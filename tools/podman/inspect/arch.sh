#!/bin/bash
set -e

sudo podman manifest inspect fedora | jq '.manifests[].platform.architecture'
