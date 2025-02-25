Test systemd Requires=
=======================

If enable/start a.service, b.service and c.service will be started, if b.service
start successfully, and c.service start failed, Then, Although c.service startup
failed. a.service will start successfully anyway if Type=simple.


```
Requires=b.service
Requires=c.service
After=b.service
enabled

┌──────────────┐       ┌─────────────┐
│              ├───────►             │
│  a.service   │       │  c.service  │
│              ├───────►             │
└───┬─────┬────┘       └─────────────┘
    │     │              disabled
    │     │              failed
    │     │
┌───▼─────▼────┐
│              │ disabled
│  b.service   │ success
│              │
└──────────────┘
```

```
c.service          a.service   c.service
------------------------------------------
Type=simple        success
Type=exec          success
Type=oneshot       failed
Type=idle          success
Type=dbus          failed      bad-setting
Type=notify        failed
Type=notify-reload failed
Type=forking       failed
```


