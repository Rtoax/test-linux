#!/bin/bash
set -e

readonly SCRIPTS_DIR=$(dirname $(realpath $0))

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
	ln -s ${SCRIPTS_DIR}/profile.d/make_tl.sh /etc/profile.d/make_tl.sh
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
		/usr/bin/patchset \
		/usr/bin/findelf \
		/usr/bin/termplot \
		/usr/bin/kconfig_compare \
		/etc/profile.d/make_tl.sh
}

case $1 in
uninstall)
	scripts_uninstall
	;;
*)
	scripts_install
	;;
esac
