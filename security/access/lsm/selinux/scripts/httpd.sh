#!/bin/bash

set -euo pipefail
# yum -y install setools-console

WWW_HTML=/var/www/html

# yum -y install httpd
# systemctl start httpd
ps auxZ | grep httpd_t
sudo semanage fcontext -l | grep $WWW_HTML

ls -Z /usr/sbin/httpd
 # system_u:object_r:httpd_exec_t:s0 /usr/sbin/httpd


