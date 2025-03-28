#!/bin/bash 
# newest-repo: https://github.com/dracut-ng/dracut-ng
# other-repo:
# - https://github.com/dracutdevs/dracut (older)
# - https://web.git.kernel.org/pub/scm/boot/dracut/dracut

sudo dracut ./initrd.img $(uname -r)
