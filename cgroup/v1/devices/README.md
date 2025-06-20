Device Whitelist Controller cgroup
==================================

# Device Whitelist Controller

## Format

`[type] [major]:[minor] [access]`

- type: `a` (all), `c` (char), or `b` (block);
	- 'all' means it applies to all types and all major and minor numbers
- major:minor: an integer or `*` for all;
- access: Access is a composition of `r` (read), `w` (write), and `m` (mknod)


## Example

```bash
$ ls -l /dev/tty
crw-rw-rw- 1 root tty 5, 0 Jun  9 14:45 /dev/tty
```

Example: char device, major=5, minor=0, forbidden write

```bash
$ echo "c 5:0 w" > devices.deny
```

Another complex example:

```bash
$ sudo sh -c 'echo "b *:* m" > /sys/fs/cgroup/devices/kubepods.slice/devices.allow'
```


# Links

- https://www.kernel.org/doc/html/latest/admin-guide/cgroup-v1/devices.html
- https://0xax.gitbooks.io/linux-insides/content/Cgroups/linux-cgroups-1.html

