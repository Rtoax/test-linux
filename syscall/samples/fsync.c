#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>


void write_journal_entry(char *entry)
{
	const char *flog = "journal.log";
	int fd = open(flog, O_WRONLY | O_CREAT | O_APPEND, 0660);

	write(fd, entry, strlen (entry));
	write(fd, "\n", 1);

	fsync(fd);
	fdatasync(fd);
	close(fd);
}

int main(void)
{
	write_journal_entry("rongtao");
	return 0;
}


