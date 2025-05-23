#!/bin/bash
set -ex

sudo dnf install -y containerd cri-tools kata-containers qemu-kvm

sudo systemctl enable --now containerd

containerd config default | tee containerd-config.toml

# Modify containerd-config.toml to add runtime io.containerd.kata.v2
#
# 1. apply this patch:
#
#        [plugins.'io.containerd.cri.v1.runtime'.containerd.runtimes]
# +
# +        [plugins."io.containerd.grpc.v1.cri".containerd.runtimes.kata]
# +          runtime_type = "io.containerd.kata.v2"
# +
#          [plugins.'io.containerd.cri.v1.runtime'.containerd.runtimes.runc]
#            runtime_type = 'io.containerd.runc.v2'
#
# TODO: modify with sed.

# 2. replace pause
sed -i 's#registry.k8s.io/pause:3.#registry.cn-hangzhou.aliyuncs.com/google_containers/pause:3.#g' containerd-config.toml

sudo cp containerd-config.toml /etc/containerd/config.toml

sudo systemctl restart containerd.service

sudo ctr plugins ls | grep kata

kata-runtime --version
kata-runtime kata-check
