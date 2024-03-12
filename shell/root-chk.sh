#!/bin/bash
#rongtao

[[  ROOT::PERMISSION ]]
{
	echo "check ROOT::PERMISSION"
	[[ $UID -ne ${root_uid} ]]  && {
		echo -e  "require root user"
		exit  $UID
	}
}
