#!/bin/bash
set -e

sudo podman pod create mypod
sudo podman pod start mypod
sudo podman pod ps

sudo podman ps -a --pod

sudo podman pod stop mypod
sudo podman pod rm mypod
