#!/bin/bash
# refs:
# - https://github.com/kata-containers/kata-containers/blob/main/docs/install/container-manager/containerd/containerd-install.md
set -ex

sudo dnf install -y containerd cri-tools kata-containers qemu-kvm

sudo systemctl enable --now containerd

containerd config default | tee containerd-config.toml

# Modify containerd-config.toml to add runtime io.containerd.kata.v2
#
# 1. add kata runtime config, example config-kata.toml
# 2. replace pause
sed -i 's#registry.k8s.io/pause:3.#registry.cn-hangzhou.aliyuncs.com/google_containers/pause:3.#g' containerd-config.toml

sudo cp containerd-config.toml /etc/containerd/config.toml

sudo systemctl restart containerd.service

sudo ctr plugins ls | grep kata

kata-runtime --version
kata-runtime kata-check
