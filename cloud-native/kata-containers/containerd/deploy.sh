#!/bin/bash
# refs:
# - https://github.com/kata-containers/kata-containers/blob/main/docs/install/container-manager/containerd/containerd-install.md
set -ex

sudo dnf install -y containerd cri-tools kata-containers qemu-kvm

sudo systemctl enable --now containerd

containerd config default | tee containerd-config.toml

# Modify containerd-config.toml to add runtime io.containerd.kata.v2
#
# 1. add kata runtime
#
# [plugins]
#   [plugins."io.containerd.grpc.v1.cri"]
#     [plugins."io.containerd.grpc.v1.cri".containerd]
#       default_runtime_name = "kata"
#       [plugins."io.containerd.grpc.v1.cri".containerd.runtimes]
#         [plugins."io.containerd.grpc.v1.cri".containerd.runtimes.kata]
#           runtime_type = "io.containerd.kata.v2"
#
# TODO: modify with sed.

# 2. replace pause
sed -i 's#registry.k8s.io/pause:3.#registry.cn-hangzhou.aliyuncs.com/google_containers/pause:3.#g' containerd-config.toml

sudo cp containerd-config.toml /etc/containerd/config.toml

sudo systemctl restart containerd.service

sudo ctr plugins ls | grep kata

kata-runtime --version
kata-runtime kata-check
