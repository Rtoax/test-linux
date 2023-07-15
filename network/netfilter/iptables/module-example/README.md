# Xtables/iptables Module Example

## Introduction

This project is a simplification of the basic sample module from the well-known e-book "Writing Netfilter modules" (attached) by Jan Engelhardt and Nicolas Bouliane. The sample is an iptables module (which, BTW, is very different from a "Netfilter module") which simply prints some data from every packet that traverses it.

I still recommend reading the book at least once. The reason why I need a dumbed down version of it is because the original has bloat code, which I've needed to clean one too many times (ie two). To wit:

- It has a LOT of glue code for kernel versions long forgotten.
- For some reason, it feels overly concerned about the Xtables-addons project, or fiddling with the iptables code, which to me are optional, pointless and annoying steps (if you're just learning/developing/testing).

## Summary

This is how I understand it. An iptables module is two things:

1. A kernel module. This thing is the actual binary that lifts all the weight. The idea is that it hooks itself up to your network stack and does whatever it wants to the packets that traverse it. It can be a "match" or a "target" (though that's irrelevant here. See the book).
2. An userspace shared object. This is apparently optional, but I have no idea how to make things work without it. Basically, the kernel module is just a chunk of binaries living in your kernel, and by default it handles no packets. The userspace SO is like an custom iptables rule, appendable via a `iptables` command, which leads packets to the kernel module.

In other words, the user inserts the module, which starts doing nothing. The user then tells iptables to use the module by issuing a `iptables` command, which defines which packets should go to the module. iptables uses the shared object to interface with the module.

The `mod` folder contains the sample module. The `usr` folder contains the sample shared object.

## Installation

### Module

	# apt-get install linux-headers-$(uname -r)
	$ cd mod
	$ make # this generates the binary xt_ipaddr.ko.
	# make modules_install
	# depmod

After the first time, you can omit the `apt-get` and the `depmod`.

To activate it, you can modprobe it like any other module:

	# modprobe xt_ipaddr

Except, you don't actually need to do it, since `iptables` automatically modprobes for you when you use the shared object in the next section.

(also, you can use `insmod` instead of `modprobe` if you don't want to install and can afford to insert manually.) 

### SO

First time only:

	# apt-get install iptables-dev pkg-config

Compile and install:

	$ cd usr
	$ make # this generates the binary libxt_ipaddr.so.
	# make install

Note that the "install" target is just a `cp`, so it can be reverted effortlessly.

(I'm not very fluent with `pkg-config`, so I don't know how to make this a thing without actually installing.)

## Running

	node A	(192.0.2.1) ----- node B (192.0.2.5)

Insert the module and the rule by running this on node A. 

	# iptables -A INPUT -m ipaddr --ipsrc 192.0.2.5

That means "insert match 'ipaddr' on the input chain. Send the argument `--ipsrc 192.0.2.5` to ipaddr". For more information on the `iptables` command, please see generic iptables documentation.

(The code to handle --ipsrc is in the SO .c file. Look it up.)

Then send packets (eg. ping) from node B. The module will start printing our garbage in node A's kernel ring buffer. View the buffer by running

	$ dmesg

Keep in mind that, whenever you need to change the code, you need to remove the old module manually. They're separate components; reinserting the rule does not automatically replace the module. Also, you need to remove all the relevant rules before Linux will let you remove the module.

	# iptables -D INPUT -m ipaddr --ipsrc 192.0.2.5 # remove the rule.
	# sudo modprobe -r xt_ipaddr # remove the module.

## License

Copyright © 2014 ydahhrk <-@->  
This work is free. You can redistribute it and/or modify it under the
terms of the Do What The Fuck You Want To Public License, Version 2,
as published by Sam Hocevar. See the COPYING file for more details.

(The original version of this code belongs to Jan Engelhardt, see the book.)
