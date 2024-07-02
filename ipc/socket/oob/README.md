## TCP Out-of-Band Data

* in-band 正常的 normal 数据
* Out-of-Band 紧急的数据需要 quickly 发送的数据,忽略 流控制 和 拥塞问题，高优先级
* UDP 没有带外数据

Many transport layers have the concept of out-of-band data, which is sometimes called expedited data. The idea is that something important occurs at one end of a connection and that end wants to tell its peer quickly. By "quickly" we mean that this notification should be sent before any "normal" (sometimes called "in-band") data that is already queued to be sent, and should be sent regardless of any flow control or blocking issues. That is, out-of-band data is considered higher priority than normal data. Instead of using two connections between the client and server, out-of-band data is mapped onto the existing connection.

Unfortunately, once we get beyond the general concepts and down to the real world, almost every transport layer has a different implementation of out-of-band data. As an extreme example, UDP has no implementation of out-of-band data. In this chapter, we will focus on TCP's model of out-of-band data, provide numerous small examples of how it is handled by the sockets API, and describe how it is used by applications like telnet, rlogin, and FTP. Other than remote interactive applications like these, it is rare to find any use for out-of-band data.

TCP does not have true out-of-band data. Instead, TCP provides an urgent mode. Assume a process has written N bytes of data to a TCP socket and that data is queued by TCP in the socket send buffer, waiting to be sent to the peer. We show this in Figure 24.1 and have labeled the data bytes 1 through N.

The process now writes a single byte of out-of-band data, containing the ASCII character a, using the send function and the `MSG_OOB` flag.

```c
send(fd, "a", 1, MSG_OOB);
```

What happens if we send multiple bytes of out-of-band data, as in

```c
send(fd, "abc", 3, MSG_OOB);
```

