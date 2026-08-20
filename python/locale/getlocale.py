#!/bin/env python

import locale
import sys

def supports_unicode():
    try:
        loc = locale.getlocale(locale.LC_CTYPE)
        if loc and 'UTF-8' in loc[1].upper():
            return True
        for var in ('LC_ALL', 'LC_CTYPE', 'LANG'):
            if 'UTF-8' in os.environ.get(var, '').upper():
                return True
    except:
        pass
    return False

if supports_unicode:
    print("Support unicode")
