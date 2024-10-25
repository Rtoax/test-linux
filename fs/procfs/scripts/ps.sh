#!/bin/bash
# see ps(1)
#
# Copyright (C) 2023-2024, Co.
#
# 2023-05-06	Rong Tao	Create this.

ps_info()
{
	ps -A -o stat,ppid,pid,lstart,comm
}

ps_zombie()
{
	ps_info | grep -e '^[Zz]'
}

ps_D()
{
	ps_info | grep ^D
}

ps_sleep()
{
	ps_info | grep ^S
}

ps_mem_rss()
{
	local pid=$$

	# -O rss: show rss columns
	ps -O rss ${pid}
}

ps_sleep
