#!/bin/bash
# Build Container Image of test-linux
#
# NOTE: only call this in top Makefile
#
set -ex

_image=fedora:latest
_tag=test-linux:latest

podman build --build-arg IMAGE=$_image --tag ${_tag} -f $PWD/Dockerfile
