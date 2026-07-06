#!/bin/bash
set -e

create_fs() {
	sudo dd if=/dev/zero of=lower.ext4 bs=4096 count=4096
	sudo mkfs -t ext4 lower.ext4
	sudo cp lower.ext4 upper.ext4
}

mount_fs() {
	mkdir lower upper merged

	sudo mount lower.ext4 lower
	sudo mount upper.ext4 upper
	sudo chown "$USER:$USER" lower upper
}

# Unmount the overlay and observe state.
umount_fs() {
	sudo umount merged
	echo "--------- after umount merged ---------"
	sudo tree lower upper/upper upper/work merged

	sudo umount upper
	sudo umount lower
}

create_fs
mount_fs

printf 'lower-content' > lower/lower-file
mkdir -p lower/tmp/

# Note: workdir and upperdir must reside under the same mount.
mkdir -p upper/{upper,work}
printf 'upper-content' > upper/upper/upper-file

# Work must be empty. E.g. this would be bad:
#printf work-content > upper/work/work-file

# Make the lower readonly to show that that is possible:
# writes actually end up on the upper filesystem.
sudo mount -o remount,ro lower.ext4 lower

# Create the overlay mount.
sudo mount -t overlay overlay \
	-o lowerdir=lower,upperdir=upper/upper,workdir=upper/work \
	merged

# Create files in overlayfs
printf 'overlay-content' > merged/overlay-file
touch merged/tmp/$(mktemp -u file-XXXXXX)

echo "--------- merged ---------"
sudo tree lower upper/upper upper/work merged

# Write to underlying directories while mounted
# gives undefined behaviour.
#printf lower-content-2 > lower/lower-file-2
#printf upper-content-2 > upper/upper-file-2

umount_fs

# Cleanup.
sudo rm lower.ext4 upper.ext4
sudo rmdir lower upper merged
