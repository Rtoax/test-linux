#include <netinet/in.h>

socklen_t inet6_rth_space(int type, int segments);
void *inet_rth_init(void *rthbuf, socklen_t rthlen, int type, int segment);
int inet6_rth_add(void *rthbuf, const struct in6_addr *addr);
int inet6_rth_reverse(const void *in, void *out);
int inet6_rth_segments(const void *rthbuf);
struct in6_addr *inet6_rth_getaddr(const void *rthbuf, int index);

int main(void)
{
	return 0;
}
