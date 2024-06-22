#!/bin/bash

. config.sh

make clean
make

echo "Listen on ${SOCK_VHOST_PATH}"
./vhost-user ${SOCK_VHOST_PATH}
