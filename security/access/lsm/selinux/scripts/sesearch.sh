#!/bin/bash

# yum -y install setools-console

WWW_HTML=/var/www/html

# yum -y install httpd
# systemctl start httpd
ps auxZ | grep httpd_t
sudo semanage fcontext -l | grep "$WWW_HTML"
sudo semanage fcontext -l | grep "/var/www" | more
sudo sesearch --allow | grep "allow httpd_t httpd_sys_content_t "
