#!/bin/bash

# Check all images
crictl images

# Check all pods
crictl pods
crictl pods --name [NAME]

# Check running container
crictl ps -a

# Exec a container
crictl exec -ti ID bash

# Update container
crictl update --cpu-period 1000000 --cpu-quota 1000000 [CONTAINER ID]
