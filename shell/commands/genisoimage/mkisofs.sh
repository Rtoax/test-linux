#!/bin/bash

mkisofs -r -o output.iso \
   -b isolinux/isolinux.bin -c isolinux/boot.cat \
   -no-emul-boot -boot-load-size 4 -boot-info-table \
   CD_root
