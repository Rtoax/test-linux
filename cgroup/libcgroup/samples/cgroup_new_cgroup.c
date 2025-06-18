#include <libcgroup.h>

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>


#define CGRP_NAME "test_cgroup"

int main(int argc, char **argv)
{
	pid_t pid;
	struct cgroup *cgrp = NULL;
	struct cgroup_controller *cgroup_controller;
	int ret = 0;

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

	ret = cgroup_create_cgroup(cgrp, 0);
	if (ret) {
		fprintf(stderr, "Failed to create cgroup %s, %s\n", CGRP_NAME,
			cgroup_strerror(cgroup_get_last_errno()));
		ret = 1;
		goto free;
	}

	cgroup_controller = cgroup_add_controller(cgrp, "memory");
	if (!cgroup_controller) {
		fprintf(stderr, "Error adding memory controller to cgroup\n");
		ret = 1;
		goto delete;
	}

	/* 100M */
	size_t limit_in_bytes = 100 * 1024 * 1024;
	ret = cgroup_set_value_uint64(cgroup_controller, "memory.limit_in_bytes", limit_in_bytes);
	if (ret) {
		fprintf(stderr, "Error setting memory limit: %d\n", ret);
		ret = 1;
		goto delete;
	}

	limit_in_bytes = 0;
	cgroup_get_value_uint64(cgroup_controller, "memory.limit_in_bytes", &limit_in_bytes);
	printf("Set memory.limit_in_bytes to %ld\n", limit_in_bytes);

	pid = fork();
	if (pid < 0)
		goto delete;

	/* TODO: cgroup OOM test, why not OOM???????????? */
	if (pid == 0) {
		size_t i;

		sleep(1);
		printf("Child running...\n");

		mlockall(MCL_CURRENT | MCL_FUTURE);
		char *mem = malloc(limit_in_bytes * 10);
		/* page fault */
		for (i = 0; i < limit_in_bytes * 10; i += getpagesize())
			mem[i] = 'a';

		exit(1);
	}

	printf("Attaching pid %d to cgroup.\n", pid);
	ret = cgroup_attach_task_pid(cgrp, pid);
	if (ret) {
		fprintf(stderr, "Error attaching task to cgroup: %d\n", ret);
		ret = 1;
		goto delete;
	}

	waitpid(pid, NULL, 0);

delete:
	cgroup_delete_cgroup(cgrp, 0);
free:
	cgroup_free_controllers(cgrp);
	cgroup_free(&cgrp);
	return ret;
}
