#include <unistd.h>
#include <limits.h>
#include <string>
#include <iostream>

/* /usr/include/c++/${version}/filesystem */
#ifdef __cpp_lib_filesystem // C++ >= 17 && HOSTED
# pragma message "Define __cpp_lib_filesystem"
#endif

#if __has_include(<filesystem>)
#include <filesystem>
namespace std_filesystem = std::filesystem;
#elif __has_include(<experimental/filesystem>)
#include <experimental/filesystem>
namespace std_filesystem = std::experimental::filesystem;
#else
#error "neither <filesystem> nor <experimental/filesystem> are present"
#endif

std::string do_readlink(std::string const &path)
{
	char buff[PATH_MAX];
	ssize_t len =::readlink(path.c_str(), buff, sizeof(buff) - 1);

	if (len != -1) {
		buff[len] = '\0';
		return std::string(buff);
	}
	/* handle error condition */
	return nullptr;
}

int main(void)
{
	std::string path = "/etc/system-release";
	std::string link = do_readlink(path);

	std::cout << path << " link is " << link << std::endl;

#if __GNUC_PREREQ(8, 6)
	std::string path2 = "/bin/ls";
	std_filesystem::path abs_path = std_filesystem::canonical(path2);
	std::cout << path2 << " absolute path is " << abs_path << std::endl;
#endif

	return 0;
}
