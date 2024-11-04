#!/bin/bash
set -ex

name=container-volume

podman volume create ${name}
podman volume ls
podman volume inspect ${name}

podman run --rm -ti -v ${name}:/data fedora:latest bash

podman volume remove ${name}
podman volume ls
