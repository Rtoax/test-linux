#pragma once

#define __hotpatch(N, M)	__attribute__((hotpatch(N, M)))

/* Override -fpatchable-function-entry=N,M */
#define __patchable(N, M)	__attribute__((patchable_function_entry(N, M)))
