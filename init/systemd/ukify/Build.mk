include os.mk
prog-$(call is_os,debian fedora) += build.sh
