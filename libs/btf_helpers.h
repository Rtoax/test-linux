// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
#pragma once
#include <stdbool.h>

struct btf *btf_load_vmlinux(void);
struct btf *btf_load_module(const char *module, struct btf **base);

void print_btf(const struct btf *btf);
const char *btf_kind_name(int kind);

int btf_has_ksym(const struct btf *btf, const char *ksym, int *kind);
int btf_has_kfunc(const struct btf *btf, const char *kfunc, bool dump);
int btf_has_struct(const struct btf *btf, const char *sname, bool dump);
int btf_has_union(const struct btf *btf, const char *sname);
int btf_has_enum(const struct btf *btf, const char *sname);
int btf_has_enum64(const struct btf *btf, const char *sname);
int btf_has_decl_tag(const struct btf *btf, const char *ksym);
