# Chapter 7: XDP and iproute2 as a loader

**VERY VERY VERY IMPORTANT NOTE ON LOCKING YOURSELF OUT OF THE MACHINE**: The code in this example basically filters all the TCP packets to a given network interface. If you are connected via SSH to this machine, make sure to use another interface or change the program accordingly. The Vagrant environment already does this if you need a quick win!

In the machine:

Enter into this example folder:

```bash
cd ~/linux-observability-with-bpf/code/chapter-7/iproute2
```

You can now use the `compile.sh` script to create the `program.o` ELF file.


Now that you have it, you can load the program to an interface. We will use `eth1` again because the program
blocks TCP packets and we are connected to the Vagrant machine trough SSH :)

```bash
sudo ip link set dev eth1 xdp obj program.o sec mysection
```


Please note that you can see that the program was loaded by doing an `ip a` and looking for `xdpgeneric` in the `eth` network interface.


To unload the program you have to do:

```bash
sudo ip link set dev eth1 xdp off
```
