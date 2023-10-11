#define UNSOCKET_PATH   "/tmp/fd-pass.socket"
#define handle_error(msg) do { perror(msg); exit(EXIT_FAILURE); } while(0)