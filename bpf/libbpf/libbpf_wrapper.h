#pragma once

int tl_bpf_xdp_attach(int ifindex, int prog_fd, int xdp_flags);
int tl_bpf_xdp_detach(int ifindex, int xdp_flags);
