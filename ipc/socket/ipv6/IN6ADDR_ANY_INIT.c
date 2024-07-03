/**
 * Any Address
 * An IPv6 address consisting of 128 zero bits, written as 0::0, or just ::,
 * is the IPv6 unspecified address. In an IPv6 packet, the unspecified address
 * can appear only as the source address in packets sent by a node that is
 * bootstrapping, before the node learns its IPv6 address.
 * In the sockets API, this address is called the wildcard address. Specifying
 * it, for example, to bind for a listening TCP socket, indicates that the
 * socket will accept client connections destined to any of the node's
 * addresses. It is referenced as in6addr_any or IN6ADDR_ANY_INIT.
 *
 * Loopback Address
 * An IPv6 address consisting of 127 zero bits and a single one bit, written
 * as ::1, is the IPv6 loopback address. In the sockets API, it is referenced
 * as in6addr_loopback or IN6ADDR_LOOPBACK_INIT.
 */
#include <netinet/in.h>

static struct in6_addr tl_in6_addr_any = IN6ADDR_ANY_INIT;
static struct in6_addr tl_in6_addr_loopback = IN6ADDR_LOOPBACK_INIT;

int main(void)
{
	(void)tl_in6_addr_any;
	(void)tl_in6_addr_loopback;
	return 0;
}
