#!/bin/bash
# https://milestone-of-se.nesuke.com/en/sv-advanced/selinux/selinux-summary/

# You must `yum -y install attr`

rm -f test1.txt
touch test1.txt

#
getfattr -m security.selinux -d test1.txt
 # file: test1.txt
 #security.selinux="unconfined_u:object_r:admin_home_t:s0"
setfattr -n security.selinux -v system_u:object_r:httpd_sys_content_t:s0 test1.txt
getfattr -m security.selinux -d test1.txt
 # file: test1.txt
 #security.selinux="system_u:object_r:httpd_sys_content_t:s0"

ls -Z test1.txt
 #-rw-r--r--. root root system_u:object_r:httpd_sys_content_t:s0 test1.txt

chcon -t httpd_sys_rw_content_t test1.txt

ls -Z test1.txt
 #-rw-r--r--. root root system_u:object_r:httpd_sys_rw_content_t:s0 test1.txt

sudo restorecon -RFv test1.txt
 #restorecon reset /root/test1.txt context system_u:object_r:httpd_sys_rw_content_t:s0->system_u:object_r:admin_home_t:s0
