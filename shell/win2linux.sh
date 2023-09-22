#!/bin/sh
# 荣涛 
#windows "\r\n" to "\n"
#or delete ^M
function win2linux()
{
	sed -i 's/\r$//' $*
}
