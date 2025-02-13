SHELL = bash
include ../../tlbuild.mk



all:
	timeout 2 gpg --list-keys || true

clean:
	rm -f os-release.txt
