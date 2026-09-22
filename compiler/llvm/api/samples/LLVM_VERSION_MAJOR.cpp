#include <iostream>
#include <llvm/Config/llvm-config.h>

using namespace std;

int main(int argc, char **argv)
{
	std::cout << "LLVM_VERSION_MAJOR " << LLVM_VERSION_MAJOR << std::endl;
	std::cout << "LLVM_VERSION_MINOR " << LLVM_VERSION_MINOR << std::endl;
	std::cout << "LLVM_VERSION_PATCH " << LLVM_VERSION_PATCH << std::endl;
	std::cout << "LLVM_VERSION_STRING " << LLVM_VERSION_STRING << std::endl;
	return 0;
}
