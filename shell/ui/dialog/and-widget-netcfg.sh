#!/bin/bash

network=(
	IP:  10.0.2.15
	Netmask: 255.255.255.0
	GateWay: 10.0.2.254
	NameServer: 10.0.2.1
)

width=0
hight=0

dialog \
              --keep-window --begin 10 2 --inputbox IP ${hight} ${width} 10.0.2.15 \
 --and-widget --keep-window --begin 15 2 --inputbox Netmask ${hight} ${width} 255.255.255.0 \
 --and-widget --keep-window --begin 20 2 --inputbox GateWay ${hight} ${width} 10.0.2.254 \
 --and-widget --keep-window --begin 25 2 --inputbox NameServer ${hight} ${width} 10.0.2.1

