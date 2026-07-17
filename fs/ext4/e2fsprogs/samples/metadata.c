#include <stdio.h>
#include <ext2fs/ext2_fs.h>
#include <ext2fs/ext2fs.h>

int main(int argc, char *argv[])
{
	errcode_t ret;
	ext2_filsys fs;
	const char *block;

	if (argc < 2) {
		fprintf(stderr, "Usage: %s [block|file]\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	block = argv[1];

	ret = ext2fs_open(block, EXT2_FLAG_RW, 0, 0, unix_io_manager, &fs);
	if (ret) {
		fprintf(stderr, "open failed: %ld\n", ret);
		exit(EXIT_FAILURE);
	}

	printf("Block size      : %u\n", fs->blocksize);
	printf("Inode count     : %u\n", fs->super->s_inodes_count);
	printf("Free inodes     : %u\n", fs->super->s_free_inodes_count);
	printf("Block count     : %lld\n", ext2fs_blocks_count(fs->super));
	printf("Free blocks     : %lld\n", ext2fs_free_blocks_count(fs->super));
	printf("Max mount count : %d\n", fs->super->s_max_mnt_count);

	ext2fs_close(fs);
	return 0;
}
