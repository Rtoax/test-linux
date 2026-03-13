#include <algorithm>
#include <iostream>

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
	std::cout << normalize_whitespace("   a  b  \t\tc   d   ") << std::endl;
	return 0;
}
