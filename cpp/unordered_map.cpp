#include <iostream>
#include <unordered_map>

typedef void (*fn1_t)(void);

#define FUNC_DEBUG()	std::cout << "Calling " << __func__ << ": " << __LINE__ << std::endl;

class func_map {
private:
	std::unordered_map<std::string, fn1_t> fn1_map_;
public:
	void register_fn1(const std::string& key, fn1_t func) {
		fn1_map_[key] = func;
	}

	fn1_t get_fn1(const std::string& key) {
		auto iter = fn1_map_.find(key);
		if (iter != fn1_map_.end()) {
			return iter->second;
		}
		return nullptr;
	}

	void call_fn1(const std::string& key) {
		fn1_t func = get_fn1(key);
		if (func != nullptr) {
			func();
		} else {
			std::cerr << "Error: Function '" << key << "' not found!" << std::endl;
		}
	}
};

void foo1(void)
{
	FUNC_DEBUG();
}

int main(void)
{
	func_map funcMap;

	funcMap.register_fn1("foo1.0", foo1);
	funcMap.register_fn1("foo1.1", foo1);
	funcMap.register_fn1("foo1.2", foo1);

	funcMap.call_fn1("foo1.1");
	funcMap.call_fn1("__not_exist__");

	return 0;
}
