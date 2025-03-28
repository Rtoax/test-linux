Name:		initramfs
Version:	0.0.1
Release:	1%{?dist}
Summary:	Linux initramfs
License:	GPLv2
URL:		https://github.com/rtoax/test-linux

%global InitramfsVersion	%{version}-%{release}.%{_target_cpu}
%global RootDir			/home/rongtao/


%description
The Linux initramfs image.


%prep
echo "prep..."

%build
echo "Build..."


%install
mkdir -p $RPM_BUILD_ROOT/%{RootDir}
touch $RPM_BUILD_ROOT/%{RootDir}/initramfs-%{InitramfsVersion}.img


%post
echo "post..."


%preun
echo "preun..."


%postun
echo "postun..."


%posttrans
echo "posttrans..."
pushd %{RootDir}
touch initramfs-%{InitramfsVersion}.img
rm -f initramfs.img
ln -s initramfs-%{InitramfsVersion}.img initramfs.img
popd


%files
# ghost: not included in rpm package, but in rpm record metadata.
%ghost %{RootDir}/initramfs-%{InitramfsVersion}.img
%ghost %{RootDir}/initramfs.img


%changelog
* Wed Jul 05 2023 Rong Tao <rtoax@foxmail.com> - 0.0.0-1
- Make a initramfs.img link.

* Thu Jun 29 2023 Rong Tao <rtoax@foxmail.com> - 0.0.1-0
- First version.
