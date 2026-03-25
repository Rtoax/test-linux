#!/bin/bash
set -e

rpm -q --queryformat='%{version}-%{release}\n' linux-firmware 2>/dev/null
