#!/bin/bash
set -e

wget gitlab.manjaro.org/packages/core/manjaro-keyring/-/raw/master/manjaro.gpg
# or
gpg --keyserver keyserver.ubuntu.com --search-keys Manjaro Build Server

gpg --import manjaro.gpg
gpg --verify manjaro.iso.sig manjaro.iso
