#!/bin/env python
import os

from blivet.blivet import Blivet

import logging
log = logging.getLogger("anaconda.storage")

__all__ = ["create_storage"]

def create_storage():
    """Create the storage object.

    :return: an instance of the Blivet's storage object
    """
    return InstallerStorage()

class InstallerStorage(Blivet):
    """ Top-level class for managing installer-related storage configuration. """

    def __init__(self):
        super().__init__()

    @property
    def usable_disks(self):
        """Disks that can be used for the installation.

        :return: a list of disks
        """
        # Get all devices.
        devices = self.devicetree.devices

        # Add the hidden devices.
        if conf.target.is_image:
            devices += [
                d for d in self.devicetree._hidden
                if d.name in self.devicetree.disk_images
            ]
        else:
            devices += self.devicetree._hidden

        # Filter out the usable disks.
        disks = []
        for d in devices:
            if d.is_disk and not d.format.hidden and not d.protected:
                # Unformatted DASDs are detected with a size of 0, but they should
                # still show up as valid disks if this function is called, since we
                # can still use them; anaconda will know how to handle them, so they
                # don't need to be ignored anymore.
                if d.type == "dasd":
                    disks.append(d)
                elif d.size > 0 and d.media_present:
                    disks.append(d)
            # TODO: we need RAID disk as target disk
            elif d in self.mdmembers:
                log.debug("======== Found RAID Disk ========")
                print("======== Found RAID Disk ========")
                disks.append(d)

        # Remove duplicate names from the list.
        return sorted(set(disks), key=lambda d: d.name)

# Target and Configuration just for test
class Target():
    def __init__(self):
        self.is_image = False

class Configuration():
    def __init__(self):
        self.target = Target()

conf = Configuration()
storage = create_storage()
storage.reset()

log.debug(storage.devicetree)
print(storage.usable_disks)
