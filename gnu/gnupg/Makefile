SHELL = bash
ifeq ($(V),1)
  Q =
else
  Q = @
  MAKEFLAGS += --no-print-directory
endif
export Q



all:
	timeout 2 gpg --list-keys || true

clean:
	rm -f os-release.txt
