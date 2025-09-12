/**
 * Care about /etc/fstab changes
 *
 * Access /etc/fstab command line example:
 * $ findmnt --verify
 * $ findmnt --verify --fstab --tab-file /path/to/fstab
 *
 * If /etc/fstab be modified with wrong line, It will be restored to the way
 * it was before the modification.
 *
 * 2023-03-24	Rong Tao	Create this.
 * 2023-03-25	Rong Tao	vim will delete old /etc/fstab
 * 2023-03-27	Rong Tao	Add findmnt verify, support echo, vim
 */
#include <stdio.h>
#include <unistd.h>
#include <sys/select.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <sys/inotify.h>
#include <signal.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <syslog.h>


#define ARRAY_SIZE(arr) (sizeof(arr)/sizeof(arr[0]))

#define FSTAB_INOTIFY_EVENT \
				IN_ACCESS | \
				IN_MODIFY | \
				IN_CLOSE_WRITE | \
				IN_CLOSE_NOWRITE | \
				IN_OPEN | \
				IN_DELETE_SELF | \
				IN_MOVE_SELF

static int inotify_fd = -1;
static int watch_fd = -1;
static const char *etc_fstab = "/etc/fstab";
static const char *tmp_fstab = "/tmp/fstab.fstabd.backup";
static long int cnt_ops = 0;

/* log level debug */
static bool debug = false;

/* print stdio */
static bool stdio = false;

/* running on background */
static bool daemonize = false;

#define stdio_log(fmt...) do { \
		if (stdio) \
			fprintf(stdout, fmt); \
	} while (0)

/* journalctl */
#define ldebug(fmt...) do { \
		if (!debug) \
			break; \
		stdio_log(fmt); \
		syslog(LOG_DEBUG, fmt); \
	} while (0)
#define linfo(fmt...) do { \
		stdio_log(fmt); \
		syslog(LOG_INFO, fmt); \
	} while (0)
#define lwarning(fmt...) do { \
		stdio_log(fmt); \
		syslog(LOG_WARNING, fmt); \
	} while (0)
#define lerror(fmt...) do { \
		stdio_log(fmt); \
		syslog(LOG_ERR, fmt); \
	} while (0)


int fstab_verify(const char *fstab);

void sig_handler(int signum)
{
	switch (signum) {
	case SIGINT:
		ldebug("catch ctrl+c\n");
		break;
	case SIGKILL:
		ldebug("catch sigkill.\n");
		break;
	case SIGQUIT:
		ldebug("catch sigquit.\n");
		break;
	/* maybe more */
	default:
		break;
	}

	inotify_rm_watch(inotify_fd, watch_fd);
	unlink(tmp_fstab);
	exit(0);
}

int copy_file(const char *in, const char *out)
{
	FILE *fi, *fo;
	char buf[1];
	int ret = 0;

	fi = fopen(in, "r");
	if (!fi) {
		lerror("open %s failed\n", in);
		ret = -errno;
		goto done;
	}
open_tmp:
	fo = fopen(out, "w");
	if (errno == EACCES) {
		lerror("errno: %s\n", strerror(errno));
		/**
		 * If permission denied, remove the old one, create a new one.
		 */
		unlink(out);
		goto open_tmp;
	}

	while (!feof(fi)) {
		if (fread(buf, 1, 1, fi) <= 0)
			break;
		fwrite(buf, 1, 1, fo);
	}

	fclose(fi);
	fclose(fo);

done:
	return ret;
}

int backup_etc_fstab(bool skip_if_exist)
{
	if (skip_if_exist && access(tmp_fstab, F_OK) == 0) {
		ldebug("%s is exist. skip\n", tmp_fstab);
		return 0;
	}

	linfo("Backup %s to %s\n", etc_fstab, tmp_fstab);

	/**
	 * This function will open /etc/fstab, If not temporarily removed
	 * from the notification chain, it creates an endless loop.
	 */
	inotify_rm_watch(inotify_fd, watch_fd);

	/**
	 * temporary fstab may don't have write permission, make sure we can
	 * write that temporary fstab file.
	 */
	chown(tmp_fstab, getuid(), getgid());
	chmod(tmp_fstab, 0666);

	copy_file(etc_fstab, tmp_fstab);

	watch_fd = inotify_add_watch(inotify_fd, etc_fstab, FSTAB_INOTIFY_EVENT);

	return 0;
}

int restore_etc_fstab(void)
{
	int ret = 0;

	/* restore from temporary fstab file, check is exist or not */
	if (access(tmp_fstab, F_OK) != 0) {
		lerror("%s is not exist.\n", tmp_fstab);
		return -ENOENT;
	}

	if (fstab_verify(tmp_fstab) != 0) {
		lerror("%s verify failed.\n", tmp_fstab);
		return -ENOENT;
	}

	/**
	 * This function will open /etc/fstab, If not temporarily removed
	 * from the notification chain, it creates an endless loop.
	 */
	inotify_rm_watch(inotify_fd, watch_fd);

	copy_file(tmp_fstab, etc_fstab);

	watch_fd = inotify_add_watch(inotify_fd, etc_fstab, FSTAB_INOTIFY_EVENT);

	return ret;
}

int check_fs_spec(const char *fs_spec)
{
	int ret = -1;

	/* UUID= */
	if ((fs_spec[0] == 'U' && fs_spec[1] == 'U' && \
			fs_spec[2] == 'I' && fs_spec[3] == 'D'))
		ret = 0;
	/* LABEL= */
	else if ((fs_spec[0] == 'L' && fs_spec[1] == 'A' && \
			fs_spec[2] == 'B' && fs_spec[3] == 'E' && \
			fs_spec[2] == 'L'))
		ret = 0;
	/* PARTUUID= or PARTLABEL= */
	else if ((fs_spec[0] == 'P' && fs_spec[1] == 'A' && \
			fs_spec[2] == 'R' && fs_spec[3] == 'T'))
		ret = 0;
	/* /dev */
	else if ((fs_spec[0] == '/' && fs_spec[1] == 'd' && \
			fs_spec[2] == 'e' && fs_spec[3] == 'v'))
		ret = 0;

	return ret;
}

int verifier_findmnt_verify(const char *fstab)
{
	int ret = 0;
	int status = 0;
	pid_t pid;

	/****************************************
	 * Check findmnt --verify for /etc/fstab
	 ****************************************/
	pid = fork();
	/* child process */
	if (pid == 0) {
		/**
		 * $ findmnt --verify --fstab --tab-file /path/to/fstab
		 */
		char *argv[] = {
			(char *)"findmnt",
			"--verify",
			"--fstab",
			"--tab-file",
			(char *)fstab,
			"--evaluate",
			NULL
		};
		execvp(argv[0], argv);

	/* father/current process */
	} else if (pid > 0) {
		/**
		 * status = $? of 'findmnt --verify ...'
		 */
		waitpid(pid, &status, __WALL);
		if (status != 0) {
			lerror("findmnt verify %s failed: %d\n",
				fstab, status);
			ret = -EINVAL;
		}
	} else {
		/* Function not implemented */
		ret = -ENOSYS;
	}

	return ret;
}

int verifier_findmnt_verify_output(const char *fstab)
{
	int ret = 0;

	/****************************************
	 * Check findmnt --verify stdout output
	 ****************************************/
	char command[256], buffer[512];
	snprintf(command, 256, "findmnt --verify --fstab --tab-file %s --verbose 2>/dev/null", fstab);

	FILE *findmnt_pp = popen(command, "r");

	while (fgets(buffer, sizeof(buffer), findmnt_pp)) {
		/**
		 * findmnt don't figure 'unreachable source'
		 */
		if (strstr(buffer, "unreachable source")) {
			lerror("ERROR: %s", buffer);
			ret = -EINVAL;
			goto pclose;
		}
	}

pclose:
	pclose(findmnt_pp);

	return ret;
}

int verifier_fstab_each_line(const char *fstab)
{
	int ret = 0;

	/***************************************
	 * Check each line of /etc/fstab
	 ***************************************/
	int line_cnt = 0;
	FILE *contain_fp = fopen(fstab, "r");

	char fs_spec[256];
	char fs_file[128];
	char fs_vfstype[32];
	char fs_mntops[128];
	char fs_freg[8];
	char fs_passno[8];

	bool has_root = false, has_boot = false, has_efi = false;

	while (fscanf(contain_fp, "%s %s %s %s %s %s",
			fs_spec,
			fs_file,
			fs_vfstype,
			fs_mntops,
			fs_freg,
			fs_passno) != EOF) {

		if (check_fs_spec(fs_spec) == 0)
			line_cnt++;

		if (!strcmp(fs_file, "/"))
			has_root = true;
		else if (!strcmp(fs_file, "/boot")) {
			/**
			 * The order of records in fstab is important, see fstab(5)
			 */
			if (!has_root) {
				lerror("Wrong order, /boot specified befoce /.\n");
				ret = -EINVAL;
				goto fclose;
			}

			has_boot = true;
		} else if (!strcmp(fs_file, "/boot/efi")) {
			/**
			 * The order of records in fstab is important, see fstab(5)
			 */
			if (!has_boot) {
				lerror("Wrong order, /boot/efi specified before /boot.\n");
				ret = -EINVAL;
				goto fclose;
			}

			has_efi = true;
		}
	}

	if (line_cnt == 0) {
		lerror("%s don't contain valid line.\n", fstab);
		ret = -EINVAL;
	}

	if (!has_root || !has_boot) {
		lerror("not found / and /boot in %s.\n", fstab);
		ret = -EINVAL;
	}
	/* EFI boot must have /boot/efi partition */
	if (access("/sys/firmware/efi/", F_OK) == 0 && !has_efi) {
		lerror("not found /boot/efi in %s.\n", fstab);
		ret = -EINVAL;
	}

fclose:
	fclose(contain_fp);

	return ret;
}

struct verify_fn {
	int (*func)(const char *fstab);
} verifies_fn[] = {
	{ verifier_findmnt_verify },
	{ verifier_findmnt_verify_output },
	{ verifier_fstab_each_line },
};

int fstab_verify(const char *fstab)
{
	int i, ret = 0;

	/**
	 * This function will open /etc/fstab, If not temporarily removed
	 * from the notification chain, it creates an endless loop.
	 */
	if (!strcmp(fstab, etc_fstab))
		inotify_rm_watch(inotify_fd, watch_fd);

	for (i = 0; i < ARRAY_SIZE(verifies_fn); i++) {
		ret = verifies_fn[i].func(fstab);
		/* already find error */
		if (ret)
			goto done;
	}

	linfo("Verify success %s.\n", fstab);

done:
	if (!strcmp(fstab, etc_fstab))
		watch_fd = inotify_add_watch(inotify_fd, etc_fstab,
						FSTAB_INOTIFY_EVENT);

	return ret;
}

int handle_write(void)
{
	int ret = 0;

	ret = fstab_verify(etc_fstab);
	/**
	 * Wrong /etc/fstab changes was happend
	 */
	if (ret != 0) {
		lerror("%s verify failed.\n", etc_fstab);
		ret = restore_etc_fstab();
	} else if (ret == 0) {
		linfo("%s verify success.\n", etc_fstab);
		backup_etc_fstab(false);
	}

	return ret;
}

int handle_delete(void)
{
	int ret = 0;

	/**
	 * vim /etc/fstab: will create a brand new file and delete
	 * the old /etc/fstab.
	 */
	if (access(etc_fstab, F_OK) == 0) {
		handle_write();
	} else {
		restore_etc_fstab();
	}

	return ret;
}

int inotify_event_handler(struct inotify_event *event)
{
	cnt_ops++;
	ldebug("event->mask:    0x%08x, %ld", event->mask, cnt_ops);

	switch (event->mask) {
	case IN_ACCESS:
		ldebug(": Accessed\n");
		break;
	case IN_MODIFY:
		ldebug(": Modified.\n");
		break;
	case IN_CLOSE_WRITE:
		ldebug(": Close write.\n");
		handle_write();
		break;
	case IN_CLOSE_NOWRITE:
		ldebug(": Close no write.\n");
		break;
	case IN_OPEN:
		ldebug(": Opened.\n");
		backup_etc_fstab(true);
		break;
	case IN_DELETE_SELF:
		ldebug(": Deleted.\n");
		handle_delete();
		break;
	case IN_MOVE_SELF:
		ldebug(": Moved");
		handle_delete();
		break;
	default:
		ldebug("\n");
		break;
	}

	return 0;
}

enum {
	ARG_STDIO = 200,
	ARG_DEBUG,
};

void print_help(int _exit)
{
	linfo(
	"\n"
	"fstabd [OPTs] - /etc/fstab checker\n"
	"\n"
	" -f, --fstab     specify a fstab file, for test maybe, default: %s\n"
	"\n"
	" -t, --tmpfstab  specify a tmp fstab file to backup fstab\n"
	"\n"
	" --debug         set log level to debug, default: info\n"
	"\n"
	" --stdio         print log to stdio console\n"
	"\n"
	" -D, --daemon    running on background. it's will disable --stdio\n"
	"\n"
	" -h, --help      show this information\n"
	"\n"
	"you can use 'journalctl' check fstabd syslog.\n"
	"\n",
	etc_fstab
	);
	exit(_exit);
}

static int parse_args(int argc, char *argv[])
{
	struct option options[] = {
	{ "fstab",     required_argument, 0, 'f' },
	{ "tmpfstab",  required_argument, 0, 't' },
	{ "daemon",          no_argument, 0, 'D' },
	{ "debug",           no_argument, 0, ARG_DEBUG },
	{ "stdio",           no_argument, 0, ARG_STDIO },
	{ "help",            no_argument, 0, 'h' },
	{ NULL },
	};

	while (1) {
		int opt_idx;
		int c = getopt_long(argc, argv, "f:t:Dh", options, &opt_idx);
		if (c < 0)
			break;
		switch (c) {
		case 'f':
			etc_fstab = optarg;
			break;
		case 't':
			tmp_fstab = optarg;
			break;
		case 'D':
			daemonize = true;
			break;
		case 'h':
			print_help(0);
			break;
		case ARG_DEBUG:
			debug = true;
			break;
		case ARG_STDIO:
			stdio = true;
			break;
		default:
			print_help(1);
			break;
		}
	}

	if (access(etc_fstab, F_OK) != 0) {
		lerror("%s is not exist.\n", etc_fstab);
		exit(1);
	}

	if (daemonize)
		stdio = false;

	return 0;
}

int inotify_fstab_loop(void)
{
	int ret = 0;
	int len, index = 0;
	unsigned char buf[1024];
	struct inotify_event *event = NULL;

	/**
	 * vim /etc/fstab: will create a brand new file and delete the old
	 * /etc/fstab, thus, we verify the new one, if verify failed, restore
	 * from temporary fstab.
	 */
	ret = fstab_verify(etc_fstab);
	if (ret != 0) {
		restore_etc_fstab();
	} else if (ret == 0) {
		backup_etc_fstab(false);
	}

	watch_fd = inotify_add_watch(inotify_fd, etc_fstab, FSTAB_INOTIFY_EVENT);

	while (true) {
		ldebug("--------------\n");
		if ((len = read(inotify_fd, &buf, sizeof(buf))) <= 0) {
			break;
		} else {
			index = 0;
			while (index < len) {
				event = (struct inotify_event *)(buf + index);

				inotify_event_handler(event);

				index += sizeof(struct inotify_event) + event->len;
			}
		}
	}
	inotify_rm_watch(inotify_fd, watch_fd);

	return ret;
}

void check_permission(void)
{
	/* Make sure we have permission to write /etc/fstab */
	FILE *fp = fopen(etc_fstab, "a+");
	if (errno == EACCES) {
		stdio = true;
		lerror("No permission to write /etc/fstab.\n");
		exit(1);
	}
	fclose(fp);
}

int main(int argc, char *argv[])
{
	int ret;

	parse_args(argc, argv);

	/* MUST have permission */
	check_permission();

	/* Rinning on background, you don't need this in fstabd.service */
	if (daemonize)
		daemon(1, 1);

	/* Make sure the current fstab verify ok, otherwise, exit directly */
	ret = fstab_verify(etc_fstab);
	if (ret != 0) {
		lerror("%s verify failed.\n", etc_fstab);
		exit(1);
	} else if (ret == 0) {
		/* Backup /etc/fstab */
		backup_etc_fstab(false);
	}

	/* Remove temporary fstab file if exist. */
	unlink(tmp_fstab);

	signal(SIGINT, sig_handler);
	signal(SIGKILL, sig_handler);
	signal(SIGQUIT, sig_handler);

	inotify_fd = inotify_init();

	inotify_fstab_loop();

	return 0;
}

