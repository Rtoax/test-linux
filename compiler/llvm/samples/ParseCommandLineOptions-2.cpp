/**
 * https://llvm.org/docs/CommandLine.html
 */
#include <iostream>
#include <llvm/Config/llvm-config.h>
#include <llvm/Support/CommandLine.h>

using namespace llvm;
using namespace std;

int main(int argc, char **argv)
{
	cl::ParseCommandLineOptions(argc, argv);
	cl::opt<string> OutputFilename("o", cl::desc("Specify output filename"), cl::value_desc("filename"));
	cl::opt<string> InputFilename(cl::Positional, cl::desc("<input file>"), cl::init("-"));
	cl::opt<bool> Force ("f", cl::desc("Enable binary output on terminals"));
	cl::opt<bool> Quiet ("quiet", cl::desc("Don't print informational messages"));
	cl::opt<bool> Quiet2("q", cl::desc("Don't print informational messages"), cl::Hidden);

	//...
	return 0;
}
