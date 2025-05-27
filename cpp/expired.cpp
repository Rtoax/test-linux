#include <memory>
#include <iostream>

int main(void)
{
	std::shared_ptr<int> shared = std::make_shared<int>(42);
	std::weak_ptr<int> weak = shared;

	std::cout << "Before reset: " << (weak.expired() ? "Expired" : "Valid") << std::endl;

	shared.reset();

	std::cout << "After reset: " << (weak.expired() ? "Expired" : "Valid") << std::endl;
	return 0;
}
