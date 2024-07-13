#include <stdio.h>
#include <string.h>
#include <jemalloc/jemalloc.h>


//arenas.create (unsigned, extent_hooks_t *) rw
//	Explicitly create a new arena outside the range of automatically managed arenas, with optionally specified extent
//	hooks, and return the new arena index.
//------------
//If the amount of space supplied for storing the arena index does not equal sizeof(unsigned), no arena will be created
//, no data will be written to the space pointed by oldp, and *oldlenp will be set to 0.

//arena.<i>.extent_hooks (extent_hooks_t *) rw

#define PRINT_FUNC() printf("%s\n", __func__);

void *my_extent_alloc( extent_hooks_t *extent_hooks,
								  void *new_addr,
								  size_t size,
								  size_t alignment,
								  bool *zero,
								  bool *commit,
								  unsigned arena_ind){PRINT_FUNC();static char str[1024] = "Hello";return str;}
bool my_extent_dalloc( extent_hooks_t *extent_hooks,
							  void *addr,
							  size_t size,
							  bool committed,
							  unsigned arena_ind){PRINT_FUNC();return true;}
void my_extent_destroy( extent_hooks_t *extent_hooks,
								  void *addr,
								  size_t size,
								  bool committed,
								  unsigned arena_ind){PRINT_FUNC();return ;}
bool my_extent_commit( extent_hooks_t *extent_hooks,
								  void *addr,
								  size_t size,
								  size_t offset,
								  size_t length,
								  unsigned arena_ind){PRINT_FUNC();return true;}
bool my_extent_decommit( extent_hooks_t *extent_hooks,
								  void *addr,
								  size_t size,
								  size_t offset,
								  size_t length,
								  unsigned arena_ind){PRINT_FUNC();return true;}
bool my_extent_purge_forced( extent_hooks_t *extent_hooks,
							  void *addr,
							  size_t size,
							  size_t offset,
							  size_t length,
							  unsigned arena_ind){PRINT_FUNC();return true;}
bool my_extent_purge_lazy( extent_hooks_t *extent_hooks,
							  void *addr,
							  size_t size,
							  size_t offset,
							  size_t length,
							  unsigned arena_ind){PRINT_FUNC();return true;}
bool my_extent_split( extent_hooks_t *extent_hooks,
							  void *addr,
							  size_t size,
							  size_t size_a,
							  size_t size_b,
							  bool committed,
							  unsigned arena_ind){PRINT_FUNC();return true;}
bool my_extent_merge(extent_hooks_t *extent_hooks,
							  void *addr_a,
							  size_t size_a,
							  void *addr_b,
							  size_t size_b,
							  bool committed,
							  unsigned arena_ind){PRINT_FUNC();return true;}


extent_hooks_t my_extent_hooks = {
	.alloc = &my_extent_alloc,
	.commit = &my_extent_commit,
	.dalloc = &my_extent_dalloc,
	.decommit = &my_extent_decommit,
	.destroy = &my_extent_destroy,
	.merge = &my_extent_merge,
	.purge_forced = &my_extent_purge_forced,
	.purge_lazy = &my_extent_purge_lazy,
	.split = &my_extent_split,
};


void set_jemalloc_arena_i_extent_hooks(unsigned iarena)
{
	unsigned narenas, i;
	size_t mib[3];
	size_t len, miblen;

	len = sizeof(narenas);
	je_mallctl("arenas.narenas", &narenas, &len, NULL, 0);
	printf("narenas = %ld.\n", narenas);

	miblen = 3;

	je_mallctlnametomib("arena.0.extent_hooks", mib, &miblen);
	for (i = 0; i < narenas; i++) {
		if(i!=iarena) continue;

		printf("Set extent_hooks of %d arena.\n", iarena);

		extent_hooks_t extent_hooks;


		mib[1] = i;
		len = sizeof(extent_hooks);
		je_mallctlbymib(mib, miblen, (void *)&extent_hooks, &len, NULL, 0);

		je_mallctlbymib(mib, miblen, NULL, NULL, (void *)&my_extent_hooks, sizeof(my_extent_hooks));
	}
}

void get_jemalloc_arenas_create(unsigned *value)
{
	size_t size = sizeof(unsigned);
	je_mallctl("arenas.create", value, &size, NULL, 0);
}

void get_jemalloc_arenas_create_with_extent_hooks(unsigned *value, extent_hooks_t *hooks)
{
	size_t size = sizeof(unsigned);
	printf(">>value = %d\n", *value);
//	je_mallctl("arenas.create", value, &size, hooks, sizeof(extent_hooks_t));//这里不知道为什么不可以
	je_mallctl("arenas.create", value, &size, NULL, 0);
	printf(">>value = %d\n", *value);
}


int main()
{
	printf("MALLCTL_ARENAS_ALL = %ld\n", MALLCTL_ARENAS_ALL);

	unsigned value = 1;

	get_jemalloc_arenas_create(&value);
	printf("value = %d\n", value);
	set_jemalloc_arena_i_extent_hooks(value);

	value = 1;


	get_jemalloc_arenas_create_with_extent_hooks(&value, &my_extent_hooks);
	printf("value = %d\n", value);
	set_jemalloc_arena_i_extent_hooks(value);


}

