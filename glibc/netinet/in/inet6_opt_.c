#include <netinet/in.h>

#if 0
int inet6_opt_init(void *extbuf, socklen_t extlen);
int inet6_opt_append(void *extbuf, socklen_t extlen, int offset, uint8_t type,
		     socklen_t len, uint8_t align, void **databufp);
int inet6_opt_finish(void *extbuf, socklen_t extlen, int offset);
int inet6_opt_set_val(void *databuf, int offset, const void *val,
		      socklen_t vallen);

int inet6_opt_next(const void *extbuf, socklen_t extlen, int offset,
		   uint8_t *type, socklen_t *lenp, void **databufp);
int inet6_opt_find(const void *extbuf, socklen_t extlen, int offset,
		   uint8_t type, socklen_t *lenp, void **databufp);
int inet6_opt_get_val(const void *databuf, int offset, void *val,
		      socklen_t vallen);
#endif

int main(void)
{
	return 0;
}
