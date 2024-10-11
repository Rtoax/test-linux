#!/bin/bash
set -e

FILE=os-release.txt

cp /etc/os-release ${FILE}

# Sign
gpg --sign ${FILE}
gpg --verify ${FILE}.gpg

# Extract
gpg --output ${FILE}.out --decrypt ${FILE}.gpg

# sig contains orig and key
gpg --output ${FILE}.sig --clearsign ${FILE}

# Create asc file
gpg --armor --detach-sig ${FILE}
gpg --verify ${FILE}.asc ${FILE}

gpg --list-keys
#uid           [ revoked] Joshua Strot <joshua@manjaro.org>
gpg --delete-keys        'Joshua Strot'
