#!/bin/bash

. config.sh

rm -f ${SOCK_VHOST_PATH}

echo "Listen on ${SOCK_VHOST_PATH}"
nc --unixsock --listen ${SOCK_VHOST_PATH}
