#!/bin/bash

SRPM_ROOT=$PWD/srpm

# git submodule update srpm/
mkdir -p ${SRPM_ROOT}/SOURCES
mkdir -p ${SRPM_ROOT}/SPECS

cp README.md ${SRPM_ROOT}/
cp fstabd.spec ${SRPM_ROOT}/SPECS
cp fstabd.service ${SRPM_ROOT}/SOURCES
cp fstabd.sh ${SRPM_ROOT}/SOURCES
cp fstabd.conf ${SRPM_ROOT}/SOURCES

pushd ${SRPM_ROOT}/
rpmbuild -ba --define "_topdir ${SRPM_ROOT}" SPECS/fstabd.spec
popd
