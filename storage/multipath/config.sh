#!/bin/bash

# Install device mapper multipath package
sudo dnf install -y device-mapper-multipath

# Generating and Exploring the default device mapper configuration file
#  Show help info
sudo mpathconf --help
#  The devices which are set by default need not to be set again.
#  This will create a sample /etc/multipath.conf
sudo mpathconf --enable --find_multipaths y

# Editing the multipath.conf file
#  The below command will generate a file in the multipath directory.
sudo mpathconf --enable --user_friendly_names y

# Enabling the Multipathd service
sudo systemctl start multipathd
sudo systemctl enable multipathd

# Blacklisting of some devices
#  blacklist {
#      devnode vda
#  }
#  In the above example, the device vda will be ignored or blacklisted during
#  the multi-mapper search.

