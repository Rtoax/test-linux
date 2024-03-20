#ifndef _COMMON_H
#define _COMMON_H

#define PATH "/tmp/UNIX"

#define HELLO       "Hello"
#define GOODBYE     "Goodbye"
#define QUIT        "Quit"

#define MAX_CLIENT_NUM      10 /* FD_SETSIZE */

#define debug() fprintf(stderr, "%s:%d\n", __func__, __LINE__)

#endif /*<_COMMON_H>*/
