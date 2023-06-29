Name:		initramfs
Version:	5.10.0
Release:	0
Summary:	Linux initramfs
License:	GPLv2
URL:		http://cclinux.org

%global InitramfsVersion	%{version}-%{release}.%{_target_cpu}

%description
The Linux initramfs image.


%prep
echo "prep..."

%build
echo "Build..."


%install
mkdir -p $RPM_BUILD_ROOT/home/rongtao/
dd if=/dev/zero of=$RPM_BUILD_ROOT/home/rongtao/initramfs-%{InitramfsVersion}.img bs=1M count=20


%post
echo "post..."


%files
%ghost /home/rongtao/initramfs-%{InitramfsVersion}.img


%changelog
* Thu Jun 29 2023 Rong Tao <rongtao@cestc.cn> - 5.10.0-0
- First version.
