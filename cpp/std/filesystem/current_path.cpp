#include <iostream>
#include <filesystem>

int main(void)
{
	std::filesystem::path cwd = std::filesystem::current_path();
	std::cout << "Current working directory: " << cwd << std::endl;
	std::cout << "\t: " << cwd.string() << std::endl;
}
