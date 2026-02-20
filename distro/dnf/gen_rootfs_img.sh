#!/bin/bash
# Step by step to make a rootfs.img
#
# 2022-06-29	Rong Tao	Create this
#
set -e

ARCH=`uname -m`

BaseOS_NAME=tmp-baseos
BaseOS_REPO=$BaseOS_NAME.repo

AppStream_NAME=tmp-appstream
AppStream_REPO=$AppStream_NAME.repo

DST_PATH=$PWD/tmp-dvd-rootfs.out

rootfs_FILE=rootfs.img
rootfs_SIZE_MB=3000
export rootfs_PATH=$DST_PATH

mount_rootfs_dir()
{
	test ! -d $rootfs_PATH && mkdir -p $rootfs_PATH
	sudo mount $rootfs_FILE $rootfs_PATH
}

# return 0: create new rootfs
# return 1: rootfs already exist
function create_rootfs_dir()
{
	test -f $rootfs_FILE && echo "=== exist $rootfs_FILE" && exit 1

	echo "=== create rootfs"

	RPMs_tmp_dir=$PWD/tmp-dvd-rpms-dir

	# Make repo files
	cat <<-END >>$BaseOS_REPO
	[$BaseOS_NAME]
	name=Test BaseOS
	baseurl=http://yum.cestc.cn/repo/centos/22.09.2/BaseOS/$ARCH/os/
	gpgcheck=0
	enabled=0
	END

	cat <<-END >>$AppStream_REPO
	[$AppStream_NAME]
	name=Test AppStream
	baseurl=http://yum.cestc.cn/repo/centos/22.09.2/AppStream/$ARCH/os/
	gpgcheck=0
	enabled=0
	END

	# Move tmp repo to system /etc/yum.repos.d/
	sudo cp $BaseOS_REPO $AppStream_REPO /etc/yum.repos.d/

	# Create rootfs.img and Mount it
	dd if=/dev/zero of=$rootfs_FILE bs=1M count=$rootfs_SIZE_MB
	mkfs.ext4 $rootfs_FILE
	mount_rootfs_dir

	# Make tmp dir
	mkdir -p $RPMs_tmp_dir

	sudo rpm --root $rootfs_PATH --initdb

	sudo dnf --disablerepo=* --enablerepo=tmp-* \
		install --downloadonly --downloaddir $RPMs_tmp_dir -y \
			centos-repos \
			centos-release \
			centos-gpg-keys

	sudo rpm --root $rootfs_PATH -ivh $RPMs_tmp_dir/centos-*
	sudo rpm --root $rootfs_PATH --import $rootfs_PATH/etc/pki/rpm-gpg/RPM-GPG-KEY-centosofficial

	# Delete tmp repo from Host OS
	sudo rm /etc/yum.repos.d/$AppStream_REPO /etc/yum.repos.d/$BaseOS_REPO

	# Add tmp-repo to rootfs
	sudo rm $rootfs_PATH/etc/yum.repos.d/*
	sudo mv $BaseOS_REPO $AppStream_REPO $rootfs_PATH/etc/yum.repos.d/

	sudo rm -rf $RPMs_tmp_dir

	return 0
}

###############################################################################
# <group>

install_img_rpms=(
	abattis-cantarell-fonts acl adwaita-cursor-theme adwaita-icon-theme alsa-lib anaconda-core anaconda-gui
	anaconda-widgets atk at-spi2-atk at-spi2-core attr audit audit-libs augeas-libs authselect authselect-libs
	bash bind-license bind-utils binutils biosdevname blivet-data boost-regex brotli bubblewrap bzip2 bzip2-libs
	ca-certificates cairo cairo-gobject
	centos-gpg-keys centos-release centos-logos
	chkconfig chrony
	colord-libs coreutils coreutils-common cpio cracklib cracklib-dicts crda createrepo_c createrepo_c-libs
	crypto-policies crypto-policies-scripts cryptsetup cryptsetup-libs cups-libs curl cyrus-sasl-lib daxctl-libs
	dbus-common dbus-daemon dbus-libs dbus-tools dbus-x11 dconf dejavu-sans-mono-fonts device-mapper
	device-mapper-event-libs device-mapper-libs device-mapper-multipath device-mapper-multipath-libs
	device-mapper-persistent-data dmidecode dnf dnf-data dosfstools dracut dracut-squash dwz e2fsprogs
	e2fsprogs-libs ed efibootmgr efi-srpm-macros efivar-libs elfutils elfutils-debuginfod-client
	elfutils-default-yama-scope elfutils-libelf elfutils-libs enchant2 ethtool expat fcoe-utils
	file findutils flatpak-libs fontconfig freetype fribidi fstrm fuse fuse-common fuse-libs gawk gcr gdb
	gdb-headless gdbm-libs gdisk gdk-pixbuf2 gdk-pixbuf2-modules gettext gettext-libs ghc-srpm-macros glib2
	glibc glibc-common glibc-langpack-en glib-networking gmp gnupg2 gnutls gobject-introspection go-srpm-macros
	gpgme graphite2 grep groff-base grub2-common grub2-tools grub2-tools-efi grub2-tools-extra grub2-tools-minimal
	gsettings-desktop-schemas gssproxy gstreamer1 gstreamer1-plugins-base gtk3 gtk-update-icon-cache gzip
	harfbuzz harfbuzz-icu hdparm hexedit hicolor-icon-theme hostname hunspell hunspell-en-US hwdata hyphen
	ima-evm-utils initscripts ipcalc ipmitool iproute iptables iputils iscsi-initiator-utils
	iscsi-initiator-utils-iscsiuio isns-utils-libs iso-codes isomd5sum iw iwl1000-firmware
	iwl100-firmware iwl105-firmware iwl135-firmware iwl2000-firmware iwl2030-firmware
	iwl3160-firmware iwl5000-firmware iwl5150-firmware iwl6000g2a-firmware
	iwl6000g2b-firmware iwl6050-firmware iwl7260-firmware jansson jbigkit-libs json-c json-glib
	kbd kbd-misc kexec-tools keybinder3 keyutils keyutils-libs kmod kmod-libs kpartx krb5-libs
	langtable lcms2 less libacl libaio libarchive libassuan libatasmart libattr libbabeltrace libbasicobjects
	libblkid libblockdev libblockdev-crypto libblockdev-dm libblockdev-fs libblockdev-kbd
	libblockdev-loop libblockdev-lvm libblockdev-mdraid libblockdev-mpath libblockdev-nvdimm
	libblockdev-part libblockdev-swap libblockdev-utils libbpf libbytesize libcap libcap-ng
	libcollection libcom_err libcomps libcurl libdaemon libdatrie libdb libdnf libdrm libedit libepoxy
	libestr libevent libfastjson libfdisk libffi libfontenc libgcc libgcrypt
	libglvnd libglvnd-egl libglvnd-gles libglvnd-glx libgnomekbd libgomp libgpg-error libgudev libgusb
	libibverbs libICE libicu libidn2 libini_config libipt libjpeg-turbo libkcapi libkcapi-hmaccalc
	libksba libmaxminddb libmnl libmodulemd libmount libndp libnfsidmap libnghttp2 libnl3 libnl3-cli
	libnma libnotify libogg libpath_utils libpciaccess libpkgconf libpng libproxy libpsl libpwquality
	libref_array librepo libreport libreport-anaconda libreport-cli libreport-gtk libreport-plugin-reportuploader
	librsvg2 libseccomp libsecret libselinux libsemanage libsepol libsigsegv libSM libsmartcols libsolv libsoup
	libss libssh libssh-config libstdc++ libtasn1 libtdb libteam libthai libtimezonemap libtirpc libtool-ltdl
	libudisks2 libunistring libusbx libuser libutempter libuuid libuv libverto libvorbis libwayland-client
	libwayland-cursor libwayland-egl libwayland-server libwebp libX11 libX11-common libX11-xcb libXau
	libxcb libXcomposite libxcrypt libXcursor libXdamage libXdmcp libXext libXfixes libXfont2 libXft
	libXi libXinerama libxkbcommon libxkbfile libxklavier libxml2 libXmu libXrandr libXrender libxshmfence
	libxslt libXt libXtst libXv libXxf86vm libyaml libzstd linux-firmware lldpad llvm-libs lmdb-libs
	lsof lua-libs lvm2 lvm2-dbusd lz4-libs lzo mdadm mesa-dri-drivers mesa-libEGL mesa-libgbm mesa-libGL
	mesa-libglapi mokutil mpfr mtools mtr ncurses ncurses-base ncurses-libs ndctl ndctl-libs nettle
	net-tools NetworkManager NetworkManager-initscripts-updown NetworkManager-libnm nfs-utils
	nm-connection-editor npth nspr nss nss-softokn nss-softokn-freebl nss-sysinit nss-util nvme-cli
	ocaml-srpm-macros openblas-srpm-macros openjpeg2 openldap openssh openssh-clients openssh-server
	openssl-libs orc os-prober ostree ostree-libs p11-kit p11-kit-trust pam pango parted patch
	pciutils pciutils-libs pcre pcre2 perl-Carp perl-constant perl-Encode perl-Errno perl-Exporter
	perl-File-Path perl-File-Temp perl-Getopt-Long perl-HTTP-Tiny perl-interpreter perl-IO perl-libs
	perl-MIME-Base64 perl-parent perl-PathTools perl-Pod-Escapes perl-podlators perl-Pod-Perldoc
	perl-Pod-Simple perl-Pod-Usage perl-Scalar-List-Utils perl-Socket perl-srpm-macros perl-Storable
	perl-Term-ANSIColor perl-Term-Cap perl-Text-ParseWords perl-Text-Tabs+Wrap perl-Time-Local pigz
	pixman pkgconf pkgconf-m4 pkgconf-pkg-config platform-python plymouth plymouth-scripts policycoreutils
	polkit polkit-libs polkit-pkla-compat popt prefixdevname procps-ng protobuf-c psmisc
	publicsuffix-list-dafsa python39 python3-argcomplete python3-blivet python3-cairo
	python3-chardet python3-dasbus python3-dbus python3-dnf python3-gobject-base python3-idna python3-libs
	python3-meh python3-meh-gui python3-pid python3-pip-wheel python3-productmd python3-pysocks python3-pytz
	python3-pyudev python3-pyyaml python3-requests python3-requests-file python3-requests-ftp
	python3-setuptools-wheel python3-simpleline python3-six python3-systemd python3-urllib3 python-srpm-macros
	quota quota-nls rdma-core readline realmd redhat-rpm-config rpm rpm-build rpm-plugin-selinux rsync rsyslog
	rust-srpm-macros satyr sed selinux-policy selinux-policy-targeted setup sg3_utils shadow-utils
	shared-mime-info smartmontools snappy source-highlight sqlite-libs strace syslinux syslinux-nonlinux
	systemd systemd-libs systemd-pam systemd-udev tar teamd tigervnc-server-minimal tmux tpm2-tss tzdata
	udisks2 udisks2-iscsi unzip usbutils userspace-rcu util-linux vim-minimal volume_key-libs webkit2gtk3
	webkit2gtk3-jsc wget which woff2 wpa_supplicant xfsdump xfsprogs xkeyboard-config xmlrpc-c
	xmlrpc-c-client xorg-x11-server-utils xorg-x11-xauth
	xz xz-libs yelp yelp-libs yelp-xsl zip zlib zstd
)


###############################################################################
# <category>
Install_Img=(
	${install_img_rpms[@]}
)

###############################################################################
# Install rpms
install_rpms_list_baseos()
{
#	sudo dnf --installroot=$rootfs_PATH clean all
#	sudo dnf --installroot=$rootfs_PATH makecache
	sudo dnf --installroot=$rootfs_PATH \
		install -y \
		--disablerepo=* --enablerepo="$BaseOS_NAME,$AppStream_NAME" \
		$@
}

rpm_command()
{
	echo "rpm $@"
	sudo rpm --root $rootfs_PATH $@
}

rootfs_tmp_clean()
{
	test -d $rootfs_PATH && \
		sudo umount $rootfs_PATH && \
		rmdir $rootfs_PATH
	rm -f $BaseOS_REPO $AppStream_REPO
}

###############################################################################
# __main__

gen_rootfs_img()
{
	case $1 in
	new)
		create_rootfs_dir
		install_rpms_list_baseos ${Install_Img[@]}
		rootfs_tmp_clean
		;;
	install)
		mount_rootfs_dir
		install_rpms_list_baseos ${Install_Img[@]}
		rootfs_tmp_clean
		;;
	rpmlist)
		mount_rootfs_dir
		rpm_command -qa
		rootfs_tmp_clean
		;;
	clean)
		rootfs_tmp_clean
		;;
	help|*)
		echo "usage: $0 [new|install|rpmlist|clean]"
		;;
	esac
}

if [ "$0" = "./gen_rootfs_img.sh" ]; then
	gen_rootfs_img $@
fi
