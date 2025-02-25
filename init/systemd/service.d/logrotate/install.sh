#!/bin/bash
# Test logrotate service

. uninstall.sh

sudo cp logrotate.service /usr/lib/systemd/system/
sudo cp logrotate.timer /usr/lib/systemd/system/
sudo cp logrotate /usr/local/bin/
sudo cp logrotate.d/logrotate /etc/logrotate.d/
sudo mkdir /var/log/logrotate/

sudo systemctl daemon-reload
sudo systemctl start logrotate.timer
sudo systemctl status logrotate.timer

