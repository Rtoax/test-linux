#ifndef _COMMON_H
#define _COMMON_H

#define PATH "./UNIX.sock"

#define HELLO       "Hello"
#define GOODBYE     "Goodbye"
#define QUIT        "Quit"

#define MAX_CLIENT_NUM      10 /* FD_SETSIZE */

#ifdef DEBUG
# define debug() fprintf(stderr, "%s:%d\n", __func__, __LINE__)
#else
# define debug()
#endif

#endif /*<_COMMON_H>*/
