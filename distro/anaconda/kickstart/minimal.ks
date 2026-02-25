# Copyright (C) 2024-2026 Rong Tao

text
poweroff
keyboard --xlayouts='us'
lang en_US.UTF-8
cdrom

%packages
@^minimal-environment
%end

firstboot --enable

ignoredisk --only-use=vda
clearpart --none --initlabel
autopart

timezone Asia/Shanghai --utc
network --bootproto=dhcp --activate

rootpw --iscrypted $6$flCcLV.o4eVuqsKa$ZwTjjvfI96kXVdrt.8alGeczKK0BIFcCFDaYGklo82onzz/OCG7S2vLtJ5joPgpfY9ghZMqH/YAlru0w78Ejq1
user --groups=wheel --name=rongtao --password=$6$h5Zvx5VoFf5su0Bj$Z.yj6WHGobcK4yBwKdcFHKxvVEUA7f73TSZQ1liKcAz.WM3FHVmPAp3uBuvcgu95mpWzV7pLXM3RH/xIQGx6T0 --iscrypted --gecos="rongtao"

eula --agreed

%post --interpreter=/bin/sh
# The following two lines could skip eula licenses and 'c' continue produce.
# For example, in kylin V10SP3.
systemctl disable initial-setup.service
systemctl disable initial-setup-reconfiguration.service
poweroff
%end
