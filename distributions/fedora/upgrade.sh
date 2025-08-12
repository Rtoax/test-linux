#!/bin/bash
# ref: https://www.linuxcapable.com/how-to-upgrade-fedora-release/
set -e

newest_fedora=42

# update your system to ensure all packages are current
sudo dnf upgrade --refresh -y
# Cleaning up your existing Fedora system by removing old packages is a good idea
sudo dnf autoremove -y
# install the DNF-plugin-system-upgrade package
sudo dnf install dnf-plugin-system-upgrade -y
# run the system-upgrade command to download the Fedora release
sudo dnf system-upgrade download --releasever=${newest_fedora} --allowerasing -y

# If the –allowerasing option does not work, you may need to re-sync your
# Fedora 37 system using the following command:
#sudo dnf distro-sync
# If you’ve exhausted all other options and are still encountering issues,
# running an SELinux reset may help
#sudo fixfiles -B onboot
# Once you have completed the initial steps, enter the following command to
# download the necessary packages for the upgrade process:
#sudo dnf system-upgrade download --releasever=

# Reboot, and a progress bar will indicate the final installation progress.
echo "WARNING: sudo dnf system-upgrade reboot -y"
exit 0

# Login

# Post Upgrade Cleanup
sudo dnf system-upgrade clean
# Removing any broken symlinks on your system is also a good idea.
sudo find /usr -type l -xtype l -delete
# If you want to see a list of all broken symlinks before cleaning them up, you can run the:
sudo symlinks -r /usr | grep dangling
# Finally, if you want to change the hostname of your Fedora system
# sudo hostnamectl set-hostname --static XXXX

