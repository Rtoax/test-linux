#!/bin/bash
set -ex

image="quay.io/fedora/fedora:42"

sudo ctr image pull ${image}
sudo ctr run --runtime "io.containerd.kata.v2" --rm -t ${image} test-kata uname -r
