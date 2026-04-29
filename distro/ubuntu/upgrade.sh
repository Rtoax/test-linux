#!/bin/bash
# Upgrade Ubuntu
# ref: https://ubuntu.com/server/docs/upgrade-introduction
# newest: 26.04
# - https://mirrors.aliyun.com/ubuntu-releases/26.04/ubuntu-26.04-desktop-amd64.iso

sudo apt install -y update-manager-core
sudo apt update -y
sudo apt dist-upgrade -y

# Check Update
sudo do-release-upgrade -c

# Upgrade
# It is recommended to upgrade the system using the do-release-upgrade command
# on Server edition and cloud images.
sudo do-release-upgrade -d

# Then, do the upgrade
sudo apt upgrade -y --fix-broken

# If you can't enter the GUI after reboot, then:
sudo apt install -y ubuntu-desktop
