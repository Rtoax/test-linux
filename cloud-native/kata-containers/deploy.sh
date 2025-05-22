#!/bin/bash
set -ex

sudo dnf install -y containerd cri-tools kata-containers qemu-kvm

sudo systemctl enable --now containerd

containerd config default | tee containerd-config.toml

# TODO: modify containerd-config.toml to add runtime io.containerd.kata.v2

sudo cp containerd-config.toml /etc/containerd/config.toml

sudo systemctl restart containerd.service

sudo ctr plugins ls | grep kata

kata-runtime --version
kata-runtime kata-check
