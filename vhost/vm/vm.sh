#!/bin/bash

. config.sh

if [[ ! -e ${SOCK_PATH} ]]; then
	echo "ERROR: Start vhost first"
	exit 1
fi

${QEMU} --enable-kvm \
	-m 1024 \
	-chardev socket,id=vhost0,path=${SOCK_PATH} \
	-netdev vhost-user,id=user0,chardev=vhost0 \
	-drive file=${IMG_QCOW2} \
	-cdrom ${IMG_ISO}

