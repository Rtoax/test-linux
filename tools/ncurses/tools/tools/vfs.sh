#!/bin/bash
set -e

sudo bpftrace -e \
'kprobe:vfs_write* {
	@write += 1;
}
kprobe:vfs_read* {
	@read += 1;
}
i:s:1 {
	printf("%ld %ld\n", @write, @read);
	clear(@write);
	clear(@read);
}
END {
	clear(@write);
	clear(@read);
}
' 2>/dev/null | ../loadavg --title 'VFS Read and Write' --ylabel 'N/s' \
			-l 'write' -l 'read'
