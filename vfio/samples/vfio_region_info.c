#include <string.h>
#include <malloc.h>
#include <fcntl.h>
#include <linux/pci_regs.h>
#include <linux/vfio.h>
#include <sys/eventfd.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <stdbool.h>

#define RTE_LOG(level, module, fmt...) printf(fmt);

/*
 * region info may contain capability headers, so we need to keep reallocating
 * the memory until we match allocated memory size with argsz.
 */
int
pci_vfio_get_region_info(int vfio_dev_fd, struct vfio_region_info **info,
		int region)
{
	struct vfio_region_info *ri;
	size_t argsz = sizeof(*ri);
	int ret;

	ri = malloc(sizeof(*ri));
	if (ri == NULL) {
		RTE_LOG(ERR, EAL, "Cannot allocate memory for region info\n");
		return -1;
	}
again:
	memset(ri, 0, argsz);
	ri->argsz = argsz;
	ri->index = region;

	ret = ioctl(vfio_dev_fd, VFIO_DEVICE_GET_REGION_INFO, ri);
	if (ret < 0) {
		free(ri);
		return ret;
	}
	if (ri->argsz != argsz) {
		struct vfio_region_info *tmp;

		argsz = ri->argsz;
		tmp = realloc(ri, argsz);

		if (tmp == NULL) {
			/* realloc failed but the ri is still there */
			free(ri);
			RTE_LOG(ERR, EAL, "Cannot reallocate memory for region info\n");
			return -1;
		}
		ri = tmp;
		goto again;
	}
	*info = ri;

	return 0;
}

int main(void)
{
	/* TODO */
	return 0;
}
