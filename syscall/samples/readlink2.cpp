#include <unistd.h>
#include <limits.h>
#include <string>
#include <iostream>


std::string do_readlink(std::string const& path)
{
	char buff[PATH_MAX];
	ssize_t len = ::readlink(path.c_str(), buff, sizeof(buff)-1);

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

	std::cout << path << ": " << link << std::endl;

	return 0;
}
