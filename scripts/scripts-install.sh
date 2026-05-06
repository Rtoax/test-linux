#!/bin/bash
set -e

readonly SCRIPTS_DIR=$(dirname $(realpath $0))

realuser=$USER
# running with sudo, we should get real user
if [[ ! -z ${SUDO_USER} ]]; then
	realuser=${SUDO_USER}
fi
if [[ ${realuser} == root ]]; then
	realhome=/root
else
	realhome=/home/${realuser}
fi

scripts_install()
{
	ln -s ${SCRIPTS_DIR}/git/bigfile.sh /usr/bin/git-bigfile
	ln -s ${SCRIPTS_DIR}/git/statistic.sh /usr/bin/git-statistic
	ln -s ${SCRIPTS_DIR}/git/statistic.py /usr/bin/git-statistic.py
	ln -s ${SCRIPTS_DIR}/git/push-remote-all.sh /usr/bin/git-push-remote-all
	ln -s ${SCRIPTS_DIR}/git/push-remote-all.sh /usr/bin/git-push-remote-all-tags
	ln -s ${SCRIPTS_DIR}/git/rm-permanent.sh /usr/bin/git-rm-permanent
	ln -s ${SCRIPTS_DIR}/patchset.sh /usr/bin/patchset
	ln -s ${SCRIPTS_DIR}/findelf.sh /usr/bin/findelf
	ln -s ${SCRIPTS_DIR}/termplot.sh /usr/bin/termplot
	ln -s ${SCRIPTS_DIR}/kconfig_compare.sh /usr/bin/kconfig_compare
	ln -s ${SCRIPTS_DIR}/kcompile.sh /usr/bin/kcompile
	ln -s ${SCRIPTS_DIR}/qemu-compile.sh /usr/bin/qemu-compile
	ln -s ${SCRIPTS_DIR}/qemu-vm.sh /usr/bin/qemu-vm

	# Other directory
	ln -s ${SCRIPTS_DIR}/../ai/pytorch/build/compile /usr/bin/pytorch-compile
	ln -s ${SCRIPTS_DIR}/../tools/heatmap/hmctl.sh /usr/bin/hmctl
}

scripts_uninstall()
{
	rm -f /usr/bin/pytorch-compile \
		/usr/bin/git-bigfile \
		/usr/bin/git-statistic \
		/usr/bin/git-statistic.py \
		/usr/bin/git-push-remote-all \
		/usr/bin/git-push-remote-all-tags \
		/usr/bin/git-rm-permanent \
		/usr/bin/hmctl \
		/usr/bin/patchset \
		/usr/bin/findelf \
		/usr/bin/termplot \
		/usr/bin/kconfig_compare \
		/usr/bin/kcompile \
		/usr/bin/pytorch-compile \
		/usr/bin/qemu-compile \
		/usr/bin/qemu-vm
}

scripts_set_env()
{
	if [[ ! -f ${realhome}/.bashrc ]]; then
		touch ${realhome}/.bashrc
	fi
	cat >>${realhome}/.bashrc<<-EOF
	source ${SCRIPTS_DIR}/make_tl.sh
	alias make='make_tl'
	EOF
}

scripts_unset_env()
{
	if [[ ! -f ${realhome}/.bashrc ]]; then
		return 0
	fi

	sed -i '/make_tl/d' ${realhome}/.bashrc
	# FIXME: remove this line after a little while
	rm -f /etc/profile.d/make_tl.sh
}

case $1 in
uninstall)
	scripts_uninstall
	scripts_unset_env
	;;
*)
	scripts_install
	scripts_set_env
	;;
esac
