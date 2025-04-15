#!/bin/env python

import sys
from importlib.metadata import distribution

package_name = "bcc"

try:
    dist = distribution(package_name)
    location = dist.locate_file('')
    files = dist.files
    print(f"The location of the package '{package_name}' is: {location}")
    for f in files:
        print(f"{location}/{f}")
except:
    print(f"Error get manifest of '{package_name}'", file=sys.stderr)

