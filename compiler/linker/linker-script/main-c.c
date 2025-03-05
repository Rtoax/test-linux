extern int foo1(void);
extern int foo2(void);
extern int bar(void);

int main1 = 1;

int main(void)
{
	main1 = 2;
	foo1();
	foo2();
	bar();
	return 0;
}
