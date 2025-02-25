#!/bin/bash

# Delete 6 hours ago journal.
sudo find /var/log/journal/ -maxdepth 2 -mmin +360 -type f -name "*.journal~" -exec rm -rf {} \;
sudo echo "Clean remote journal $(date)" >> ~/clean-hour-ago-journal.log
