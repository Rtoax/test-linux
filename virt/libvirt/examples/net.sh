#!/bin/bash

sudo virsh net-list --all
sudo virsh net-start default
sudo virsh net-autostart default
