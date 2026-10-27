include os.mk
prog-$(call is_os_any_of,debian fedora) += build.sh
