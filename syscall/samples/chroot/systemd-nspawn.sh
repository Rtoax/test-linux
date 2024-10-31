#!/bin/bash

sudo systemd-nspawn -D ~/rootfs/
# Then, you could use follow command see the container
# $ sudo machinectl list
# $ sudo machinectl status rootfs
# $ sudo machinectl show rootfs

