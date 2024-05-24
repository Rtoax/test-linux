#!/bin/bash
sudo dmidecode | grep 'Serial Number'
sudo dmidecode -s system-serial-number
