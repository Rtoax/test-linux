Network
===========

# OSI model

                  OSI model               TCP/IP
             +--------------------+  +-------------------+
    Layer 7: | Application layer  |  |                   |
             +--------------------+  |                   |
    Layer 6: | Presectation layer |  | Application layer | Layer 4
             +--------------------+  |                   |
    Layer 5: | Session layer      |  |                   |
             +--------------------+  +-------------------+
    Layer 4: | Transport layer    |  | Transport layer   | Layer 3
             +--------------------+  +-------------------+
    Layer 3: | Network layer      |  | Network layer     | Layer 2
             +--------------------+  +-------------------+
    Layer 2: | Data link layer    |  |   Network         |
             +--------------------+  |  Access Layer     | Layer 1
    Layer 1: | Physical layer     |  |                   |
             +--------------------+  +-------------------+


# Proc

- /proc/net/dev


# IPv4

Ranges for the five different classes of IPv4 addresses.

    +------------+--------+-------------------------------+
    |  usage     | class  |              range            |
    +------------+--------+-------------------------------+
    |Unicase     | A,B,C  |   0.0.0.0  ~ 223.255.255.255  |
    |Multicase   |   D    |   224.0.0.0 ~ 239.255.255.255 |
    |Experimental|   E    |   240.0.0.0 ~ 255.255.255.255 |
    +------------+--------+-------------------------------+


# Outer IPv4 Header

    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    |Version|  IHL  |Type of Service|          Total Length         |
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    |         Identification        |Flags|      Fragment Offset    |
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    |  Time to Live |Protocl=17(UDP)|   Header Checksum             |
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    |                       Outer Source IPv4 Address               |
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    |                   Outer Destination IPv4 Address              |
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+


# Outer UDP Header

    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    |           Source Port         |       Dest Port = VXLAN Port  |
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    |           UDP Length          |        UDP Checksum           |
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+


# VXLAN Header

    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    |R|R|R|R|I|R|R|R|            Reserved                           |
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    |                VXLAN Network Identifier (VNI) |   Reserved    |
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+


# Inner Ethernet Header

    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    |             Inner Destination MAC Address                     |
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    | Inner Destination MAC Address | Inner Source MAC Address      |
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    |                Inner Source MAC Address                       |
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    |OptnlEthtype = C-Tag 802.1Q    | Inner.VLAN Tag Information    |
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+


# Payload

    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    | Ethertype of Original Payload |                               |
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+                               |
    |                                  Original Ethernet Payload    |
    |                                                               |
    |(Note that the original Ethernet Frame's FCS is not included)  |
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

