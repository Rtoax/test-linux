#!/bin/bash

cpu_freq()
{
	cat /proc/cpuinfo | grep cpu | grep  MHz | sed -e 's/.*:[^0-9]//'
}


