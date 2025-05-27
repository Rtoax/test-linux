#pragma once
#include "qcow2.h"

int qcowhdr_check_magic(QCowHeader *hdr);
void display_qcowhdr(QCowHeader *hdr);
