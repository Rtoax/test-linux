UEFI Shell
==========

# Commands

## Boot from CDROM

```
UEFI Interactive Shell v2.2
EDK II
UEFI v2.70 (EDK II, 0x00010000)
Shell> map
Mapping table
      FS0: Alias(s):CD0a0b:;BLK2:
          PciRoot(0x0)/Pci(0x1,0x2)/Pci(0x0,0x0)/Scsi(0x0,0x0)/CDROM(0x1)
     BLK3: Alias(s):
          PciRoot(0x0)/Pci(0x1,0x4)/Pci(0x0,0x0)
     ...
Shell> fs0:

FS0:\> ls
	EFI

FS0:\> cd EFI

FS0:\EFI\> ls
	BOOT
	<vendor>

FS0:\EFI\> cd BOOT

FS0:\EFI\BOOT\> ls
	BOOTAA64.EFI
	fbaa64.efi

FS0:\EFI\BOOT\> BOOTX64.EFI
```


# Links

- https://uefi.org/sites/default/files/resources/UEFI_Shell_Spec_2_0.pdf
