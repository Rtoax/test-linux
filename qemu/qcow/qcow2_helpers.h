// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
#pragma once
#include "qcow2.h"

int qcowhdr_check_magic(QCowHeader *hdr);
void display_qcowhdr(QCowHeader *hdr);
