#!/bin/bash

echo 'scsi remove-single-device 0 0 7 0'> /proc/scsi/scsi
echo 'scsi add-single-device 0 0 7 0'> /proc/scsi/scsi
