#!/bin/bash
# refs:
# [0] https://kubernetes.io/docs/tasks/debug/debug-cluster/crictl/
# [1] https://fossies.org/linux/cri-o/tutorials/crictl.md
#

set -e

image_fedora=fedora:latest

# Check informations
sudo crictl pods
sudo crictl images
sudo crictl images -q
sudo crictl ps --all

sudo crictl pull ${image_fedora}

# Check log
sudo journalctl -u crio --no-pager

