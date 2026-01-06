// SPDX-License-Identifier: GPL-3.0
/* Copyright (C) 2026 Rong Tao */
#include <stdio.h>
#include "cuda_compat.h"
#include "cuda_helpers.h"


int main(void)
{
	cudaGraph_t graph;
	cudaGraphNode_t node;
	cudaGraphExec_t exec;

	cudaGraphCreate(&graph, 0);

	//cudaGraphAddMemcpyNode1D();

	cudaGraphDestroy(graph);
	return 0;
}
