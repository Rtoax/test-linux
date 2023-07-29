#include <fstab.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#define ARRAY_SIZE(arr) (sizeof(arr)/sizeof(arr[0]))

const char *special_file[] = {
	"/dev/sda",
	"/dev/vda",
	"/dev/mapper/control",
	"/dev/mapper/centos-root",
	NULL,
};

int main(void)
{
	int i;
	struct fstab *fstab;

	setfsent();

	for (i = 0; special_file[i]; i++) {
		fstab = getfsspec(special_file[i]);
		fprintf(stderr, "getfsspec: %s : %s\n",
				special_file[i], strerror(errno));
		if (fstab)
			break;
	}

	if (fstab) {
		printf("%s:%s:%s:%s:%s:%d:%d\n",
			fstab->fs_spec, fstab->fs_file,
			fstab->fs_vfstype, fstab->fs_mntops,
			fstab->fs_type, fstab->fs_freq, fstab->fs_passno);
	} else {
		fprintf(stderr, "Not found valide special_file.\n");
	}

	return 0;
}
