# Disk partition
part /boot --fstype="xfs" --ondisk=sda --size=1024
part /boot/efi --fstype=efi --size=200 --asprimary
part / --fstype="xfs" --ondisk=sda  --grow --size=1
