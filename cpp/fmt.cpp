/**
 * Test https://github.com/fmtlib/fmt
 */
#include <fmt/core.h>
#include <fmt/format.h>
#include <fmt/printf.h>

int main(void)
{
	std::string str = fmt::format("Hello {}", "World");
	fmt::print("Hello, world! {}\n", str);
	return 0;
}
