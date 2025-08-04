#include <assert.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <malloc.h>
#include <errno.h>


int listdir_recur(char *dir_path)
{
	int err = 0;
	DIR *dir;
	struct dirent *entry;
	size_t entry_size = PATH_MAX + 1;
	char *entry_path = malloc(entry_size);
	size_t path_len;
	struct stat st;

	/* Copy the directory path into entry_path. */
	strncpy(entry_path, dir_path, entry_size);
	path_len = strlen(dir_path);

	/* If the directory path doesn't end with a slash, append a slash. */
	if (entry_path[path_len - 1] != '/') {
		entry_path[path_len] = '/';
		entry_path[path_len + 1] = '\0';
		++path_len;
	}

	dir = opendir(dir_path);
	if (!dir) {
		err = -errno;
		goto error;
	}

	/* Loop over all directory entries. */
	while ((entry = readdir(dir)) != NULL) {
		const char *type;
		/**
		 * Build the path to the directory entry by appending the entry
		 * name to the path name.
		 */
		strncpy(entry_path + path_len, entry->d_name,
				entry_size - path_len);

		/* Determine the type of the entry. */
		lstat(entry_path, &st);
		if (S_ISLNK(st.st_mode))
			type = "symbolic link";
		else if (S_ISDIR(st.st_mode)) {
			type = "directory";
			if (strcmp(entry->d_name, ".") && strcmp(entry->d_name, ".."))
				listdir_recur(entry_path);
		} else if (S_ISCHR(st.st_mode))
			type = "character device";
		else if (S_ISBLK(st.st_mode))
			type = "block device";
		else if (S_ISFIFO(st.st_mode))
			type = "fifo";
		else if (S_ISSOCK(st.st_mode))
			type = "socket";
		else if (S_ISREG(st.st_mode))
			type = "regular file";
		else
			/* Unexpected. Each entry should be one of the types above. */
			assert(0 && "Unknown file type.");

		/* Print the type and path of the entry. */
		printf("%-18s: %s\n", type, entry_path);
	}

error:
	free(entry_path);
	closedir(dir);
	return err;
}

int main(int argc, char *argv[])
{
	char* dir_path;

	if (argc >= 2)
		dir_path = argv[1];
	else
		dir_path = ".";

	listdir_recur(dir_path);
	return 0;
}
