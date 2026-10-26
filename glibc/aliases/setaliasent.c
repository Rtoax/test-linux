#include <aliases.h>
#include <stdio.h>

int main(void)
{
	struct aliasent *ent;

	setaliasent();

	while ((ent = getaliasent())) {
		printf("%s: ", ent->alias_name);
		for (int i = 0; i < ent->alias_members_len; i++) {
			printf("%s, ", ent->alias_members[i]);
		}
		printf("%d\n", ent->alias_local);
	}

	endaliasent();

	return 0;
}
