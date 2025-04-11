#include <iostream>

using namespace std;

/**
 * std::string& replace(size_t pos, size_t len, const std::string& str);
 * std::string& replace(size_t pos, size_t len, const std::string& str, size_t subpos, size_t sublen);
 * std::string& replace(size_t pos, size_t len, const char* s);
 * std::string& replace(size_t pos, size_t len, const char* s, size_t n);
 * std::string& replace(size_t pos, size_t len, size_t n, char c);
 */
int replace(void)
{
	std::string str1("1234567890");
	std::string str2("abc");

	std::cout << "str1 " << str1 << std::endl;
	str1.replace(2, 3, "---");
	std::cout << "str1 " << str1 << std::endl;
	str1.replace(2, 3, str2);
	std::cout << "str1 " << str1 << std::endl;

	return 0;
}

int main(void)
{
	replace();
}
