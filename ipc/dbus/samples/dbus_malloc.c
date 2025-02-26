#include <dbus/dbus.h>

int main(void)
{
	void *mem = dbus_malloc(1024);
	dbus_free(mem);
	return 0;
}
