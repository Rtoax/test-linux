#!/bin/bash

. config.sh

rm -f ${SOCK_VHOST_PATH}

gcc vhost.c -o vhost

echo "Listen on ${SOCK_VHOST_PATH}"
./vhost ${SOCK_VHOST_PATH}
