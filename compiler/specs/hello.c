int main(void)
{
#if !defined(TEST_LINUX)
# error "Not define TEST_LINUX"
#endif
#if !defined(TEST_LINUX2)
# error "Not define TEST_LINUX2"
#endif
#if !defined(TEST_LINUX3)
# error "Not define TEST_LINUX3"
#endif
#if !defined(TEST_LINUX10)
# error "Not define TEST_LINUX10"
#endif
	return 0;
}
