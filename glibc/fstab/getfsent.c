#include <fstab.h>
#include <stdio.h>


int main(void)
{
	setfsent();

	struct fstab *fstab = getfsent();

	printf("%s:%s:%s:%s:%s:%d:%d\n",
			fstab->fs_spec, fstab->fs_file,
			fstab->fs_vfstype, fstab->fs_mntops,
			fstab->fs_type, fstab->fs_freq, fstab->fs_passno);

	return 0;
}
