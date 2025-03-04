#!/bin/bash

ARCHIVE_URL=https://archives.fedoraproject.org/pub/archive/fedora/linux/atomic/21/
LOCAL_TAG=fedora
BRANCH=fedora-atomic/f21/x86_64/docker-host
CHECKOUT_DIR=checkout-dir.test

cd a.test

ostree --repo=repo init --mode=archive
ostree --repo=repo remote add --no-gpg-verify $LOCAL_TAG $ARCHIVE_URL
ostree --repo=repo pull $LOCAL_TAG $BRANCH
ostree --repo=repo refs
ostree --repo=repo ls $BRANCH
ostree --repo=repo checkout $BRANCH $CHECKOUT_DIR

cd -
