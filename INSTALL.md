Test-Linux Installtation
========================

## Install

```
$ sudo make install
```

Because add scripts to `/etc/profile.d/`, thus, you need to startup a new shell.

On Ubuntu 25.10, may you need to enable lines in `/etc/bash.bashrc` or `/etc/bashrc` for non-login shell:

```bash
if [ -d /etc/profile.d ]; then
  for i in /etc/profile.d/*.sh; do
    if [ -r $i ]; then
      . $i
    fi
  done
  unset i
fi
```


## Uninstall

```
$ sudo make uninstall
```
