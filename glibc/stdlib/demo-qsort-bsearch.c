#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct critter {
	const char *name;
	const char *species;
};

struct critter muppets[] = {
	{"Kermit", "frog"},
	{"Piggy", "pig"},
	{"Gonzo", "whatever"},
	{"Fozzie", "bear"},
	{"Sam", "eagle"},
	{"Robin", "frog"},
	{"Animal", "animal"},
	{"Rongtao", "sport"},
	{"RenShanshan", "cute"},
	{"Camilla", "chicken"},
	{"Sweetums", "monster"},
	{"Dr. Strangepork", "pig"},
	{"Link Hogthrob", "pig"},
	{"Zoot", "human"},
	{"RT&RSS", "love"},
	{"Dr. Bunsen Honeydew", "human"},
	{"Beaker", "human"},
	{"Swedish Chef", "human"}
};

int count = sizeof(muppets) / sizeof(struct critter);

int critter_cmp(const void *c1, const void *c2)
{
	return strcmp(((struct critter *)c1)->name, ((struct critter *)c2)->name);
}

void print_critter(const struct critter *c)
{
	printf("%s, the %s\n", c->name, c->species);
}

void find_critter(const char *name)
{
	struct critter target, *result;
	target.name = name;
	result = bsearch(&target, muppets, count, sizeof(struct critter),
			critter_cmp);
	if (result)
		print_critter(result);
	else
		printf("Couldn’t find %s.\n", name);
}

int main(void)
{
	int i;
	for (i = 0; i < count; i++)
		print_critter(&muppets[i]);
	printf("\n");

	qsort(muppets, count, sizeof(struct critter), critter_cmp);

	for (i = 0; i < count; i++)
		print_critter(&muppets[i]);
	printf("\n");

	find_critter("Kermit");
	find_critter("Gonzo");
	find_critter("RT&RSS");
	find_critter("Janice");
	return 0;
}
