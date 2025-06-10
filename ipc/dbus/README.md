D-Bus
======

D-Bus (short for "Desktop Bus") is a message-oriented middleware mechanism that
allows communication between multiple processes running concurrently on the
same machine.

D-Bus is an inter-process communication (IPC) mechanism initially designed to
replace the software component communications systems used by the GNOME and KDE
Linux desktop environments (CORBA and DCOP respectively).


# Processes without D-Bus

```
+----------+       +----------+
| ProcessA |       | ProcessB |
+-----+--+-+       +-----+----+
      |  |               |
      |  +------------+  |
      |               |  |
+-----+----+       +--+--+----+
| ProcessC |       | ProcessD |
+----------+       +----------+
```

# The same processes with D-Bus

```
+----------+       +----------+
| ProcessA |       | ProcessB |
+----+-----+       +----+-----+
     |                  |
+----+------------------+-----+
|           D-Bus             |
+----+------------------+-----+
     |                  |
+----+-----+       +----+-----+
| ProcessC |       | ProcessD |
+----------+       +----------+
```


# Links

- https://en.wikipedia.org/wiki/D-Bus

