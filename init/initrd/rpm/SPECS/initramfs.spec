Name:		initramfs
Version:	5.10.0
Release:	1
Summary:	Linux initramfs
License:	GPLv2
URL:		http://cclinux.org

%global InitramfsVersion	%{version}-%{release}.%{_target_cpu}
%global RootDir				/home/rongtao/


%description
The Linux initramfs image.


%prep
echo "prep..."

%build
echo "Build..."


%install
mkdir -p $RPM_BUILD_ROOT/%{RootDir}
dd if=/dev/zero of=$RPM_BUILD_ROOT/%{RootDir}/initramfs-%{InitramfsVersion}.img bs=1M count=20


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


%changelog
* Wed Jul 05 2023 Rong Tao <rongtao@cestc.cn> - 5.10.0-1
- Make a initramfs.img link.

* Thu Jun 29 2023 Rong Tao <rongtao@cestc.cn> - 5.10.0-0
- First version.
