#!/bin/bash

echo -------- Volume Group ---------
sudo vgs
sudo vgs --options vg_uuid,pv_name --noheadings --separator :
echo
echo -------- Physical Volume ---------
sudo pvs
echo
echo -------- Logical Volume  ---------
sudo lvs
