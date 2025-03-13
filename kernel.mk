# SPDX-License-Identifier: GPL-3.0

KVERSION_RAW := $(shell uname -r | grep -o '^[0-9]\.[0-9]*\.[0-9]*')
KVERSION := $(shell echo ${KVERSION_RAW} | awk -F '.' '{print $$1}')
KPATCHLEVEL := $(shell echo ${KVERSION_RAW} | awk -F '.' '{print $$2}')
KSUBLEVEL := $(shell echo ${KVERSION_RAW} | awk -F '.' '{print $$3}')

KFLAGS :=
KFLAGS += -DKVERSION=$(KPATCHLEVEL)
KFLAGS += -DKPATCHLEVEL=$(KPATCHLEVEL)
KFLAGS += -DKSUBLEVEL=$(KSUBLEVEL)

ifdef DEBUG
  $(info KVERSION = ${KVERSION}.${KPATCHLEVEL}.${KSUBLEVEL})
endif
