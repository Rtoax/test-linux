#!/bin/bash
set -e

sudo systemd-nspawn -D /home/rongtao/rootfs-arm64-fedora41/ \
		--user rongtao \
		--bind=/home/rongtao/Git:/root/Git \
		--bind=/home/rongtao/:/root/rongtao \
		--bind=/home/rongtao/Git:/home/rongtao/Git
