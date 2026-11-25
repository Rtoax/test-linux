# SPDX-License-Identifier: GPL-2.0-or-later
# Copyright (C) 2026 Rong Tao
#
# All changes to build and install RPM packages go here.
#
Name:		plotcake
# The version number must be consistent with the conf.h in the top-level
# directory.
Version:	v1.9.1
Release:	0%{?dist}
Summary:	Plot curves in linux terminal.

License:	GPL-2.0 or later
URL:		https://github.com/Rtoax/plotcake

Source0:	plotcake-v%{version}.tar.gz

# ========== build requires ==========

%if "%{toolchain}" == "clang"
BuildRequires:  clang
%else
BuildRequires:  gcc
BuildRequires:  git
%endif
BuildRequires:	glibc-devel

# ========== changelogs ==========

%changelog
* Thu Nov 19 2026 Rong Tao <rtoax@foxmail.com> - 1.9.1
- Not release yet.
