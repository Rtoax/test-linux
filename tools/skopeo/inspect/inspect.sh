#!/bin/bash
set -e

skopeo inspect --raw docker://registry.fedoraproject.org/fedora | jq '.manifests[].platform.architecture'
