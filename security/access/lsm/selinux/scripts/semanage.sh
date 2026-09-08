#!/bin/bash

# yum -y install setools-console

WWW_HTML=/var/www/html

# yum -y install httpd
# systemctl start httpd
ps auxZ | grep httpd_t
sudo semanage fcontext -l | grep $WWW_HTML

# user
sudo semanage user -l

# login
sudo semanage login -l
