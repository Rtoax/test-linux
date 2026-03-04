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

std::string normalize_whitespace(const std::string &input)
{
	std::string copy = input;
	std::string result;

	auto it = std::unique(copy.begin(), copy.end(), [](char l, char r) {
		return std::isspace(l) && std::isspace(r);
	});
	copy.erase(it, copy.end());

	return copy;
}

int main(void)
{
	replace();
	std::cout << normalize_whitespace("   a  b  \t\tc   d   ") << std::endl;
	return 0;
}
