VirtIO FS
=========

# Demo

- on hostos

```xml
<domain type='kvm'>
  <memoryBacking>
    <source type="memfd"/>
    <access mode="shared"/>
  </memoryBacking>
  <devices>
    <filesystem type="mount" accessmode="passthrough">
      <driver type="virtiofs"/>
      <binary path="/usr/libexec/virtiofsd"/>
      <source dir="/home/rongtao/Pictures"/>
      <target dir="rongtao_Pictures"/>
      <alias name="fs0"/>
      <address type="pci" domain="0x0000" bus="0x08" slot="0x00" function="0x0"/>
    </filesystem>
  </devices>
</domain>
```

- in guestos

```
mkdir pic
sudo mount -t virtiofs rongtao_Pictures pic
```


# Links

- https://gitlab.com/virtio-fs/virtiofsd
