#!/bin/env python3

import crypt,getpass

pw = getpass.getpass()
print(crypt.crypt(pw)
    if (pw == getpass.getpass("Confirm: "))
    else exit())
