#!/bin/bash
set -e

format() {
	echo -e "\033[32m---- ${@} ----\033[m"
	git log -1 --format="${@}"
}

for f in %H %h %B %T %t %P %p %an %aN %ae %aE %al %aL %ad %aD %ar %at %ai %aI \
	%as %ah %cn %cN %ce %cE %cl %cL %cd %cD %cr %ct %ci %cI %cs %ch %d %D \
	%S %e %s %f %b %B %N %GG %G? %GS %GK %GF %GP %GT %gD %gd %gn %gN \
	%ge %gE %gs
do
	format ${f}
done
