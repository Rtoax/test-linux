#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <sys/prctl.h>

#include <libcgroup.h>


#define CGRP_NAME "test_cgroup"

int main(int argc, char **argv)
{
	pid_t pid;
	struct cgroup *cgrp = NULL;
	struct cgroup_controller *memcg;
	int ret = 0;
	size_t limit_in_bytes = 100 * 1024 * 1024; /* 100M */

	ret = cgroup_init();
	if (ret) {
		fprintf(stderr, "cgroup_init failed\n");
		exit(1);
	}

	cgrp = cgroup_new_cgroup(CGRP_NAME);
	if (!cgrp) {
		fprintf(stderr, "Failed to allocate cgroup %s, %s\n", CGRP_NAME,
			cgroup_strerror(cgroup_get_last_errno()));
		exit(1);
	}

	memcg = cgroup_add_controller(cgrp, "memory");
	if (!memcg) {
		fprintf(stderr, "Error adding memory controller to cgroup\n");
		ret = 1;
		goto free;
	}

#ifdef CGROUP_V1
# define MEMORY_LIMIT	"memory.limit_in_bytes"
#else
# define MEMORY_LIMIT	"memory.max"
#endif
	/* note: some time you need to set memory.swap.max too */
	ret = cgroup_set_value_uint64(memcg, MEMORY_LIMIT, limit_in_bytes);
	if (ret) {
		fprintf(stderr, "Error setting memory limit: %d\n", ret);
		goto free;
	}

	limit_in_bytes = 0;
	cgroup_get_value_uint64(memcg, MEMORY_LIMIT, &limit_in_bytes);
	printf("Set "MEMORY_LIMIT" to %ld MB\n", limit_in_bytes / 1024 / 1024);

	ret = cgroup_create_cgroup(cgrp, 0);
	if (ret) {
		fprintf(stderr, "Failed to create cgroup %s, %s\n", CGRP_NAME,
			cgroup_strerror(cgroup_get_last_errno()));
		ret = 1;
		goto free;
	}

	pid = fork();
	if (pid < 0)
		goto delete;

	/* TODO: cgroup OOM test, why not OOM???????????? */
	if (pid == 0) {
		size_t i;

		prctl(PR_SET_NAME, "memcg-oom-test", 0, 0, 0);
		sleep(1);
		printf("Child running...\n");

		mlockall(MCL_CURRENT | MCL_FUTURE);
		char *mem = malloc(limit_in_bytes * 10);

		/* page fault */
		for (i = 0; i < limit_in_bytes * 10; i += getpagesize()) {
			mem[i] = 'a';
			if (i % (getpagesize() * 500) == 0) {
				printf(".");
				fflush(stdout);
			}
		}
		printf("\n");

#ifdef DEBUG
		sleep(100);
#endif
		exit(1);
	}

	printf("Attaching pid %d to cgroup.\n", pid);
	ret = cgroup_attach_task_pid(cgrp, pid);
	if (ret) {
		fprintf(stderr, "Error attaching task to cgroup: %d\n", ret);
		ret = 1;
		goto delete;
	}

#ifdef DEBUG
	sleep(100);
#endif

	waitpid(pid, NULL, 0);

delete:
	cgroup_delete_cgroup(cgrp, 0);
free:
	cgroup_free_controllers(cgrp);
	cgroup_free(&cgrp);
	return ret;
}
