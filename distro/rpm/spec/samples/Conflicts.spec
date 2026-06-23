Name:		rpm-test-Conflicts
Version:	0.0.1
Release:	0%{?dist}
Summary:	SPEC Conflicts
License:	GPLv2

%description
Test RPM SPEC Conflicts:.

# See openEuler 24.09 kernel.spec
Conflicts: iptables < 1.3.2-1

%install

%files

%changelog
* Tue Jun 23 2026 Rong Tao <rtoax@foxmail.com> - 0.0.1-0
- First commit.
