#!/bin/bash
set -e

cpio_decompress()
{
	cpio -idmv < file.cpio
}

cpio_compress()
{
	find . 2>/dev/null | \
		cpio -c -o > file.cpio
}

cpio_compress
cpio_decompress
