OpenVSwitch
===========


Hypervisors need the ability to bridge traffic between VMs and with the outside
world. On Linux-based hypervisors, this used to mean using the built-in L2
switch (the Linux bridge), which is fast and reliable. So, it is reasonable to
ask why Open vSwitch is used.

The answer is that Open vSwitch is targeted at multi-server virtualization
deployments, a landscape for which the previous stack is not well suited. These
environments are often characterized by highly dynamic end-points, the
maintenance of logical abstractions, and (sometimes) integration with or
offloading to special purpose switching hardware.

The Linux kernel implementation of Open vSwitch was merged into the kernel
mainline in kernel version 3.3,  which was released on March 18, 2012.


# OVN - OVN (Open Virtual Network)

OVN (Open Virtual Network) is a series of daemons for the Open vSwitch that
translate virtual network configurations into OpenFlow. OVN is licensed under
the open source Apache 2 license.


# Links

- https://www.openvswitch.org/
- https://en.wikipedia.org/wiki/Open_vSwitch
- https://github.com/openvswitch/ovs/blob/master/Documentation/intro/why-ovs.rst
- https://www.ovn.org/en/

