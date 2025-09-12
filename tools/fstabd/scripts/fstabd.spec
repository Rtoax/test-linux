# fstabd - Used to reset /etc/fstabd after a failed modification of
# /etc/fstabd.
Name:		fstabd
Version:	0.0.2
Release:	0%{?dist}
Summary:	/etc/fstab monitor and recover

License:	GPL-2.0
URL:		https://unknown.com/unknown
BuildArch:	noarch

Source0:	fstabd.service
Source1:	fstabd.sh
Source2:	fstabd.conf

BuildRequires:  systemd-rpm-macros

Requires:	coreutils
# inotifywait
Requires:	inotify-tools
# findmnt
Requires:	util-linux-core

%description
This package monitor fstab modifications. If incorrect modifications are
detected, exit and restore the original file.

%prep

%build
echo "Build"

%install
install -m 0755 -vd                     %{buildroot}%{_unitdir}
install -m 0644 -vp %{SOURCE0}          %{buildroot}%{_unitdir}/
install -m 0755 -vd                     %{buildroot}%{_libexecdir}/fstabd
install -m 0755 -vp	%{SOURCE1}			%{buildroot}%{_libexecdir}/fstabd/
install -m 0755 -vd                     %{buildroot}/etc/
install -m 0644 -vp %{SOURCE2}          %{buildroot}/etc/

%check

%files
%{_unitdir}/fstabd.service
%{_libexecdir}/fstabd/fstabd.sh
/etc/fstabd.conf

%changelog
