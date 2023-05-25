#!/bin/bash

. config.sh

rm -f ${SOCK_PATH}

echo "Listen on ${SOCK_PATH}"
nc --unixsock --listen ${SOCK_PATH}
