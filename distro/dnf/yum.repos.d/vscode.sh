#!/bin/bash
# ref: https://code.visualstudio.com/docs/setup/linux#_rhel-fedora-and-centos-based-distributions

set -e

rpm --import https://packages.microsoft.com/keys/microsoft.asc

cp vscode.repo /etc/yum.repos.d/vscode.repo

dnf check-update
dnf install code
