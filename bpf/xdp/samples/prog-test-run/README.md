# Chapter 7: Testing XDP programs

First let's gather some dependencies.

We already have the BCC python library, coming from the BCC package provisioned in the Vagrantfile, but we need
to install scapy.

```
sudo pip3 install scapy
```

Now we can take a look at our `program.c`, this program has different actions based on the destination
mac address and packet type. What we want to achieve, is to write a test suite to verify that the program behaves correctly.

Our test suite is defined in the `test_xdp.py` program, let's run it:

```bash
sudo python3 test_xdp.py
```

Expected output:

```
...
----------------------------------------------------------------------
Ran 3 tests in 5.618s

OK
```

Try to play with the XDP program in `program.c` and run the test suite again, what happens?
