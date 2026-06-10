#include <iostream>
#include <set>
#include <sstream>

struct CompareByFirst {
	bool operator()(const std::pair<std::string, std::string> &a,
			const std::pair<std::string, std::string> &b) const
	{
	        return a.first < b.first;
	}
};

int main(void)
{
	std::set<std::pair<std::string, std::string>> set1;
	std::set<std::pair<std::string, std::string>, CompareByFirst> set2;

	auto CompareByFirstLambda = [](const auto &a, const auto &b) {
		return a.first < b.first;
	};
	std::set<std::pair<std::string, std::string>,
		 decltype(CompareByFirstLambda)> set3;

	set1.insert({ "a", "b" });
	set1.insert({ "a", "c" });

	set2.insert({ "a", "b" });
	set2.insert({ "a", "c" });

	set3.insert({ "a", "b" });
	set3.insert({ "a", "c" });

	for (auto s : set1) {
		std::cout << "set1: " << s.first << ", " << s.second
			  << std::endl;
	}
	for (auto s : set2) {
		std::cout << "set2: " << s.first << ", " << s.second
			  << std::endl;
	}
	for (auto s : set3) {
		std::cout << "set3: " << s.first << ", " << s.second
			  << std::endl;
	}

	return 0;
}
