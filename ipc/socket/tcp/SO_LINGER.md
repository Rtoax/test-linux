TCP SO_LINGER
=============

Once the connection is established, we set the `SO_LINGER` socket option,
setting the `l_onoff` flag to 1 and the `l_linger` time to 0. This causes
an `RST` to be sent on a TCP socket when the connection is closed. We then
close the socket.

