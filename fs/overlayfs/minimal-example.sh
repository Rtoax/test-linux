#!/bin/bash
set -e

sudo dd if=/dev/zero of=lower.ext4 bs=4096 count=4096
sudo mkfs -t ext4 lower.ext4
sudo cp lower.ext4 upper.ext4

mkdir lower upper overlay

sudo mount lower.ext4 lower
sudo mount upper.ext4 upper
sudo chown "$USER:$USER" lower upper

printf 'lower-content' > lower/lower-file
mkdir lower/tmp/

# Note: workdir and upperdir must reside under the same mount.
mkdir upper/{upper,work}
printf 'upper-content' > upper/upper/upper-file

# Work must be empty. E.g. this would be bad:
#printf work-content > upper/work/work-file
# Make the lower readonly to show that that is possible:
# writes actually end up on the upper filesystem.
sudo mount -o remount,ro lower.ext4 lower

# Create the overlay mount.
sudo mount -t overlay \
	-o lowerdir=lower,upperdir=upper/upper,workdir=upper/work \
	none \
	overlay

# Interact with the mount.
printf 'overlay-content' > overlay/overlay-file
sudo tree lower upper/upper upper/work overlay

# Write to underlying directories while mounted
# gives undefined behaviour.
#printf lower-content-2 > lower/lower-file-2
#printf upper-content-2 > upper/upper-file-2

# Unmount the overlay and observe state.
sudo umount overlay
sudo tree lower upper/upper upper/work overlay

# Cleanup.
sudo umount upper
sudo umount lower
sudo rm lower.ext4 upper.ext4
sudo rmdir lower upper overlay
