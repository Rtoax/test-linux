#!/bin/bash
# Upgrade Debian
# ref: https://wiki.debian.org/DebianUpgrade

# First, ensure your system is up-to-date in it's current release.
sudo apt-get update
sudo apt-get upgrade
sudo apt-get full-upgrade

# If you haven't already, ensure all backups are up-to-date.

# In a text editor, replace the codename of your release with that of the next release in APT's package sources
# For instance, the line
#    deb https://deb.debian.org/debian/ buster main
# should be replaced with
#    deb https://deb.debian.org/debian/ bullseye main
#sudo vim /etc/apt/sources.list /etc/apt/sources.list.d/*

# If you are migrating to Bookworm or later, then a new repo for non-free firmware is available.
# If you wish, you can add non-free and non-free-firmware, depending on your specific needs.
# For instance, the line
#    deb https://deb.debian.org/debian/ bookworm main contrib non-free non-free-firmware
# or
#    deb https://deb.debian.org/debian/ stable main contrib non-free non-free-firmware

# Clean and update package lists
sudo apt-get clean
sudo apt-get update

# Perform the major release upgrade, removing packages if required
# Interrupting this step after downloading has completed is an excellent way to stress-test your backups
sudo apt-get upgrade
sudo apt-get full-upgrade

# Remove packages that are not required anymore
# Be sure to review this list: you may want to keep some of them
sudo apt-get autoremove

# Reboot to make changes effective (optional, but recommended)
echo "WARNING: sudo shutdown -r now"
