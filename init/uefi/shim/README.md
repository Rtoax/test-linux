shim (垫片)
===========

# BootFlow

- Normal BootFlow:
- Fallback BootFlow: see `../qemu/`
- MOK Manager:

```
  +---------------------------------------------+
  |                                             |   fallback
  |          +---------------------+       +----+--------------+
  |  +------>|EFI/BOOT/BOOTX64.EFI |------>|EFI/BOOT/fbx64.efi |
  |  |       |EFI/BOOT/BOOTAA64.EFI| +-----|EFI/BOOT/fbaa64.efi|
  |  |       +---------------------+ |     +-------------------+
  |  |                shim           |      scan all EFI/*/BOOT*.CSV
  |  |                               |      create and store Boot0001~n BootEntry
  |  |                               |      create adn store first found BootEntry
  |  |                               |
  |  |                               |
  v  |                shim           v               grub2
+----+-+     +-------------------------+    +-------------------------+   +-------+
| UEFI |---->|EFI/<vendor>/shimx64.efi |--->|EFI/<vendor>/grubx64.efi |-->|vmlinuz|
+------+     |EFI/<vendor>/shimaa64.efi|    |EFI/<vendor>/grubaa64.efi|   |       |
             +-------+-----------------+    +-------------------------+   +-------+
                     |       ^
                     |       |
                     v       |
              +--------------+--------+
              |EFI/<vendor>/mmx64.efi |
              |EFI/<vendor>/mmaa64.efi|
              +-----------------------+
                      MOK Manager
```

`fedora x64` example

```
EFI
├── BOOT
│   ├── BOOTX64.EFI
│   └── fbx64.efi
└── fedora
    ├── BOOTX64.CSV
    ├── grub.cfg
    ├── grubx64.efi
    ├── mmx64.efi
    └── shimx64.efi
```

> ISO: UEFI → /EFI/BOOT/BOOT*.efi → /EFI/BOOT/grub*.efi
>	Example:
>	EFI/BOOT/
>	├── BOOTAA64.EFI
>	├── grubaa64.efi
>	├── grub.cfg
>	└── TRANS.TBL


# Links

- https://github.com/rhboot/shim.git

