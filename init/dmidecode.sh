#!/bin/bash
# DMI - Desktop Management Interface, SMBIOS was originally named DMIBIOS.
# dmidecode inspect system hardware configuration and to enable or disable
# certain workarounds for problems with specific systems.
sudo dmidecode "$@"
