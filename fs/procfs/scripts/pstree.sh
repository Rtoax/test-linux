#!/bin/bash

pstree_parents_ancestor()
{
	local pid=$$

	# -s --show-parents: show parents
	# -a --arguments: show arguments
	pstree ${pid} -sap
}

pstree_parents_ancestor
