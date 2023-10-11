IPv6
====

# Disable IPv6

1. 修改 cmdline

```
	$ sudo vi /etc/default/grub
	GRUB_CMDLINE_LINUX="xxxxx ipv6.disable=1"
```

2. 临时修改 sysctl

```
sudo sysctl -a | grep -w disable_ipv6
```

3. NetworkManager

```
$ sudo nmcli connection modify [InterfaceName] ipv6.method "disabled"
$ sudo nmcli connection down [InterfaceName]
$ sudo nmcli connection up [InterfaceName]
```
