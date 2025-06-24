BMC and IPMI(Intelligent Platform Management Interface)
========================================================

```
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
```


# Tools

- ipmitool
- NBD

# Links

- https://github.com/openbmc/openbmc
