#!/bin/bash
set -ex

IMAGE=fedora:latest
NAME=fedora

sudo podman rm -f ${NAME} || true

sudo podman run --rm -d --privileged \
	-v /dev:/dev -v /run/systemd/:/run/systemd/ \
	--name ${NAME} ${IMAGE} /sbin/init

sudo podman exec ${NAME} ps -ef

sudo podman ps --all

# - reboot
# - init 6
# - shutdown -r now
# - shutdown --poweroff now
sudo podman exec ${NAME} shutdown --poweroff now

sudo podman ps --all
