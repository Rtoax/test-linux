#!/bin/env python
# Never run this script in your running system, if that, maybe you need to
# reboot your system to recover mounts.
import os

#from blivet.blivet import Blivet
from pyanaconda.modules.storage.devicetree.model import InstallerStorage

import logging
log = logging.getLogger("anaconda.storage")

storage = InstallerStorage()
storage.reset()

print(storage.devicetree)
