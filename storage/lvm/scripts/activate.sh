#!/bin/bash

# activate VG|LV
lvchange -ay ${VG}
vgchange -ay ${VG}

# deactivate
# WARNING: you need to deactivate vg first before $ wipefs --all --force /dev/vdb
lvchange -an ${VG}
vgchange -an ${VG}
