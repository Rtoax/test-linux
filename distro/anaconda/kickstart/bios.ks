# Disk partition
zerombr
part /boot --fstype="xfs" --ondisk=sda --size=1024
part biosboot --fstype=biosboot --ondisk=sda --size=2
part / --fstype="xfs" --ondisk=sda  --grow --size=1
