#!/bin/bash

__clr()
{
	local cur=${COMP_WORDS[COMP_CWORD]}
	COMPREPLY=($(compgen -W "--sane --clear --reset --version --help -s -c -r -v -h" -- $cur))
}

complete -F __clr clr
