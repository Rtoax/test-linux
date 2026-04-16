=======================================================
BMC and IPMI(Intelligent Platform Management Interface)
=======================================================

Architecture
------------

.. code-block:: text

    ┌──────────────────────────────────────────┐
    │              Redfish client              │
    │                                          │
    │    Ansible, PowerShell, cURL, Postman    │
    └─────┬────────────────────────────────────┘
          │                           ▲
          │ HTTPS                     │ HTTPS
          │ (GET,     RESTful         │ Rsp
          │ POST,                     │
          │ PATCH,                    │
          ▼ ...)                      │
    ┌─────────────────────────────────┴────────┐
    │              Redfish service             │
    │                                          │
    │     OpenBMC, ...                         │
    └──────────────────────────────────────────┘


Tools
-----

- ipmitool
- NBD
- i2c-tools


I2C Tools
---------

.. code-block:: text

    /smashclp> diagnose i2cdetect -l
    ....
    i2c-1408	i2c     1e7d2000.i3c-bus        I2C adapter

    /smashclp> diagnose i2cdetect -y 1408
        0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f
    00:                         -- -- -- -- -- -- -- --
    ....
    50: -- -- -- -- 54 55 56 57 -- -- -- -- 5c 5d 5e 5f
    ....


Links
-----

- https://github.com/openbmc/openbmc
