#!/bin/bash

USERNAME=rongtao
PASSWORD=xxxx

mount -t cifs //10.32.43.1/path/to/dir /mnt/samba-pub -o username=$USERNAME,password=$PASSWORD
