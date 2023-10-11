#pragma once

#define UNSOCKET_PATH   "/tmp/fd-pass.socket"
#define handle_error(msg) do { perror(msg); exit(EXIT_FAILURE); } while(0)

int *recv_fd(int socket, int n);
void send_fd(int socket, int *fds, int n);
