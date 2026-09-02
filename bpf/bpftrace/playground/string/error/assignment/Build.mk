bpftrace-y += diffsize.bt
bpftrace-y += index.bt
bpftrace-y += toolong.bt

BT_ENVS_diffsize.bt := --expect-return 1
BT_ENVS_index.bt := --expect-return 1
BT_ENVS_toolong.bt := --expect-return 1
