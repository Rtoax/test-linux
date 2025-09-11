#!/bin/bash
set -e

# may: export LIBGUESTFS_BACKEND=direct
qcow2mount()
{
	guestmount -a fedora.qcow2 -i -w fedora
}

qcow2umount()
{
	guestunmount fedora/
}

