#!/bin/bash
#
# How to running a container with containerd/ctr commandline
#
# Refs:
# - https://cloudyuga.guru/hands_on_lab/containerd
# - https://labs.iximiuz.com/courses/containerd-cli/ctr/image-management
# - https://stackoverflow.com/questions/59393496/how-to-run-docker-images-in-containerd-using-ctr-in-cli


# List containers
sudo ctr container ls
sudo ctr container list -q

# List namespace
sudo ctr ns ls

# Save image to tar archive
sudo podman save swos -o swos-export.tar

# Import a tar archive image
# ctr only recognize that tar archive who has container metadata, if import
# a tar archive created with tar command only, 'unrecognized image format'
# error will be triggerrd.
sudo ctr image import --base-name localhost/swos swos-export.tar

# Tag a image(to image.a.b.c/swos:latest)
sudo ctr image tag localhost/swos:latest image.a.b.c/swos:latest

# List images(-q, --quiet)
sudo ctr images list
sudo ctr images list -q

# Mount a image to directory
mkdir swos.out
sudo ctr image mount localhost/swos:latest $PWD/swos.out
ls -l $PWD/swos.out
sudo ctr image unmount $PWD/swos.out

# Create a container
sudo ctr container create localhost/swos:latest demo

# List container (see above)

# Run a container
# --rm: remove the container after running
# -d: detach from the task after it has started execution
sudo ctr run -d --rm localhost/swos:latest demo-2

# List task
sudo ctr task list
sudo ctr task start demo
# This will running CMD[] or entrypoint
sudo ctr run -d localhost/swos:latest demo_1

# Interact with the container
#  - start bash
sudo ctr run -d localhost/swos:latest demo_2 bash
#  - Interact enter bash
sudo ctr task exec -t --exec-id bash_2 demo_2 bash
sudo ctr task metrics demo_2
sudo ctr task kill demo_2

# Remove a container
sudo ctr container rm demo

# Remove a image
sudo ctr image remove localhost/swos:latest

fedora_test() {
	local tar_archive=fedora.tar

	if [[ ! -e ${tar_archive} ]]; then
		sudo podman save registry.fedoraproject.org/fedora:43 -o ${tar_archive}
	fi

	sudo systemctl restart containerd.service
	sudo systemctl status containerd.service | tee

	sudo ctr image import --base-name localhost/fedora ${tar_archive}

	sudo ctr image list -q

	sudo ctr run -d --rm registry.fedoraproject.org/fedora:43 demo_1 cat /etc/os-release

	sudo ctr container rm demo_1
}
