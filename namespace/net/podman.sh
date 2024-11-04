#!/bin/bash
set -ex

bridge_name=my_bridge

docker_image=fedora:latest

podman network create --driver bridge \
	--subnet 192.168.20.0/24 --gateway 192.168.20.3 \
	${bridge_name}
podman network inspect ${bridge_name}

# Network:
#
# --net=none : means no networking
# --net=host : The host driver allows us to share the host machine's network
#              namespace with a container. By doing so, the container would
#              have full access to the host's network, which is not a
#              recommended approach due to its security implications.
# --net=container:c1 : share container network
#                      podman run --name=c1 ...
#                      podman run --net=container:c1 ...
podman container run --net=${bridge_name} -itd ${docker_image} cat /etc/os-release

podman network remove ${bridge_name}
