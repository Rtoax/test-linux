#include <iostream>
#include <set>
#include <sstream>

int main(void)
{
	std::set<std::string> set1;
	set1.insert("a");
	set1.insert("b");
	set1.insert("b");

	for (auto s : set1) {
		std::cout << s << std::endl;
	}
	return 0;
}
