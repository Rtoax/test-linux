#!/bin/bash

vm_name=cclinux2209
sudo virsh inject-nmi ${vm_name}
