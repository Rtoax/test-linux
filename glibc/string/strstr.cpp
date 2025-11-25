#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>
#include <ostream>

int main(void)
{
	char *str;
	char logbuf[] = {
		"0: R1=ctx() R10=fp0\n" \
		"0: (85) call bpf_task_from_pid#89392\n" \
		"calling kernel function bpf_task_from_pid is not allowed\n" \
		"processed 1 insns (limit 1000000) max_states_per_insn 0 total_states 0 peak_states 0 mark_read 0\n"
	};
	std::string errmsg = "calling kernel function ";
	errmsg += "bpf_task_from_pid";
	errmsg += " is not allowed";

	std::cout << "LOG: " << logbuf << std::endl;
	std::cout << "errmsg: " << errmsg << std::endl;

	str = strstr(logbuf, errmsg.c_str());
	if (str != nullptr)
		std::cout << "str: " << str << std::endl;

	return 0;
}
