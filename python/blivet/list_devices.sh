#!/bin/bash
# execsnoop for ./list_devices.py

sudo lsblk --bytes -a -o NAME,SIZE,OWNER,GROUP,MODE,FSTYPE,LABEL,UUID,PARTUUID,MOUNTPOINT

sudo udevadm settle --timeout=300

sudo lvm lvs --noheadings --nosuffix --nameprefixes --unquoted --units=b -a -o vg_name,lv_name,lv_uuid,lv_size,lv_attr,segtype,origin,pool_lv,data_lv,metadata_lv,role,move_pv,data_percent,metadata_percent,copy_percent,lv_tags

sudo udevadm settle --timeout=300
