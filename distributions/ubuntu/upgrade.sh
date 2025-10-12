#!/bin/bash
# Upgrade Ubuntu
# ref: https://ubuntu.com/server/docs/upgrade-introduction

sudo apt install -y update-manager-core
sudo apt update -y
sudo apt dist-upgrade -y

# Check Update
sudo do-release-upgrade -c

# Upgrade
# It is recommended to upgrade the system using the do-release-upgrade command
# on Server edition and cloud images.
sudo do-release-upgrade -d
