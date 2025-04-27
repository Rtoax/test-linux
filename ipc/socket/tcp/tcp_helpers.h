#pragma once

void tcp_nodelay(int fd);
void tcp_cork(int fd);
void tcp_uncork(int fd);
