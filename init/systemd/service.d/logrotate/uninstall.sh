#!/bin/bash
# Test logrotate service

sudo systemctl stop logrotate.timer

test -e /usr/lib/systemd/system/logrotate.service && \
	sudo rm -f /usr/lib/systemd/system/logrotate.service
test -e /usr/lib/systemd/system/logrotate.timer && \
	sudo rm -f /usr/lib/systemd/system/logrotate.timer
test -e /usr/local/bin/logrotate && \
	sudo rm -f /usr/local/bin/logrotate
test -e /etc/logrotate.d/logrotate && \
	sudo rm -f /etc/logrotate.d/logrotate
test -d /var/log/logrotate/ && \
	sudo rm -rf /var/log/logrotate/

