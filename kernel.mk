# SPDX-License-Identifier: GPL-3.0

KERN_VERSION_RAW=$(shell uname -r | grep -o '^[0-9]\.[0-9]*\.[0-9]*')
KERN_VERSION = $(shell echo ${KERN_VERSION_RAW} | awk -F '.' '{print $$1}')
KERN_PATCHLEVEL = $(shell echo ${KERN_VERSION_RAW} | awk -F '.' '{print $$2}')
KERN_SUBLEVEL = $(shell echo ${KERN_VERSION_RAW} | awk -F '.' '{print $$3}')

KFLAGS :=
KFLAGS += -DKERN_VERSION=$(KERN_PATCHLEVEL)
KFLAGS += -DKERN_PATCHLEVEL=$(KERN_PATCHLEVEL)
KFLAGS += -DKERN_SUBLEVEL=$(KERN_SUBLEVEL)

ifdef DEBUG
  $(info KERN_VERSION = ${KERN_VERSION}.${KERN_PATCHLEVEL}.${KERN_SUBLEVEL})
endif
