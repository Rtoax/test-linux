#!/bin/bash

. config.sh

rm -f ${SOCK_VHOST_PATH}

gcc vhost-user.c -o vhost-user

echo "Listen on ${SOCK_VHOST_PATH}"
./vhost-user ${SOCK_VHOST_PATH}
