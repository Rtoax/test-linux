
struct foo {};
#if ERROR
/* error: ‘foo’ defined as wrong kind of tag */
union foo {};
#endif
union bar {};

int main(void)
{
	return 0;
}
