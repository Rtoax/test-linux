#include <stdio.h>
#include <string.h>
#include <jemalloc/jemalloc.h>

//arena.<i>.extent_hooks (extent_hooks_t *) rw
//	Get or set the extent management hook functions for arena <i>. The functions must be capable of operating on all
//	extant extents associated with arena <i>, usually by passing unknown extents to the replaced functions. In practice,
//	it is feasible to control allocation for arenas explicitly created via arenas.create such that all extents originate
//	from an application-supplied extent allocator (by specifying the custom extent hook functions during arena creation).
//	However, the API guarantees for the automatically created arenas may be relaxed -- hooks set there may be called in a
//	"best effort" fashion; in addition there may be extents created prior to the application having an opportunity to
//	take over extent allocation.
//	为arena<i> get、set管理范围的钩子函数。这个函数必须是现存的arena中，通常通过传递未知的范围给相关的函数。
//	通过 arenas.create 控制arenas的分配是可行的，TODO

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


extent_hooks_t arena0_extent_hooks;
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


void jemalloc_arena_i_extent_hooks()
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
		extent_hooks_t extent_hooks;


		mib[1] = i;
		len = sizeof(extent_hooks);
		je_mallctlbymib(mib, miblen, (void *)&extent_hooks, &len, NULL, 0);

		if(i==0){
			memcpy(&arena0_extent_hooks, &extent_hooks, sizeof(extent_hooks_t));
			printf("alloc	   = %p\n", arena0_extent_hooks.alloc);
			printf("commit	  = %p\n", arena0_extent_hooks.commit);
			printf("dalloc	  = %p\n", arena0_extent_hooks.dalloc);
			printf("decommit	= %p\n", arena0_extent_hooks.decommit);
			printf("destroy	 = %p\n", arena0_extent_hooks.destroy);
			printf("merge	   = %p\n", arena0_extent_hooks.merge);
			printf("purge_forced= %p\n", arena0_extent_hooks.purge_forced);
			printf("purge_lazy  = %p\n", arena0_extent_hooks.purge_lazy);
			printf("split	   = %p\n", arena0_extent_hooks.split);
		}

		if(i==0){
			je_mallctlbymib(mib, miblen, NULL, NULL, (void *)&my_extent_hooks, sizeof(my_extent_hooks));
		}
		je_mallctlbymib(mib, miblen, NULL, NULL, (void *)&extent_hooks, sizeof(extent_hooks));
	}
}

int main()
{
	printf("MALLCTL_ARENAS_ALL = %ld\n", MALLCTL_ARENAS_ALL);
	jemalloc_arena_i_extent_hooks();

	char *str = je_malloc(123);

	printf("str = %s\n", str);
}





