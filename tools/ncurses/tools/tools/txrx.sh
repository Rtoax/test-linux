#!/bin/bash
set -e

sudo bpftrace -e \
'kprobe:net_tx_action {
	@tx += 1;
}
kprobe:net_rx_action {
	@rx += 1;
}
i:s:1 {
	printf("%ld %ld\n", @tx, @rx);
	clear(@tx);
	clear(@rx);
}
END {
	clear(@tx);
	clear(@rx);
}
' 2>/dev/null | ../loadavg --title 'Network rx and tx action' --ylabel 'N/s' \
			-l 'tx' -l 'rx'
