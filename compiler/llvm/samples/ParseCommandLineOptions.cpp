/**
 * https://llvm.org/docs/CommandLine.html
 */
#include "llvm/Support/CommandLine.h"

using namespace llvm;

int main(int argc, char **argv)
{
	cl::ParseCommandLineOptions(argc, argv);
	//...
	return 0;
}
