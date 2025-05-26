#!/bin/bash

vm_name=almalinux9
sudo virsh inject-nmi ${vm_name}
