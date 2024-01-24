module SIG
==========


# CONFIG

- `CONFIG_MODULE_SIG`
- `CONFIG_MODULE_SIG_FORCE`
   - command line `module.sig_enforce=1`
   - `/proc/sys/module/sig_enforce`
- `CONFIG_MODULE_SIG_ALL`
- `CONFIG_MODULE_SIG_KEY`
- `CONFIG_MODULE_SIG_SHA1`
- `CONFIG_MODULE_SIG_SHA224`
- `CONFIG_MODULE_SIG_SHA256`
- `CONFIG_MODULE_SIG_SHA384`
- `CONFIG_MODULE_SIG_SHA512`


# keyctl(2)

```
$ sudo cat /proc/keys
```


# Links

- https://www.kernel.org/doc/html/latest/admin-guide/module-signing.html
- https://www.kernel.org/doc/html/v4.15/admin-guide/module-signing.html

