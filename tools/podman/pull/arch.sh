#!/bin/bash
set -e

sudo podman pull --arch=arm64 fedora:latest
sudo podman pull --platform linux/riscv64 alpine:latest
