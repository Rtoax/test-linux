extern int foo(void);
extern int bar(void);

int main1 = 1;

int main(void)
{
	main1 = 2;
	foo();
	bar();
	return 0;
}
