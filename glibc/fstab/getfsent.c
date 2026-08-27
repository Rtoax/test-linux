#include <errno.h>
#include <fstab.h>
#include <stdio.h>

int main(void)
{
	int err = 0;
	struct fstab *fstab;

	setfsent();

	fstab = getfsent();
	if (!fstab) {
		err = -ENOENT;
		goto done;
	}

	printf("%s:%s:%s:%s:%s:%d:%d\n", fstab->fs_spec, fstab->fs_file,
	       fstab->fs_vfstype, fstab->fs_mntops, fstab->fs_type,
	       fstab->fs_freq, fstab->fs_passno);

done:
	endfsent();
	return err;
}
