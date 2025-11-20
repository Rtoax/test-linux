#include <iostream>
#include <unordered_map>

typedef void (*fn1_t)(void);

#define FUNC_DEBUG()	std::cout << "Calling " << __func__ << ": " << __LINE__ << std::endl;

class func_map {
private:
	std::unordered_map<std::string, fn1_t> fn1_map_;
	std::unordered_map<std::pair<std::string, std::string>, fn1_t> fn1_map2_;
public:
	func_map() = default;

	void register_fn1(const std::string& key, fn1_t func) {
		fn1_map_[key] = func;
	}
	void register_fn1(const std::string& key1, const std::string& key2, fn1_t func) {
		fn1_map2_[{key1, key2}] = func;
	}

	fn1_t get_fn1(const std::string& key) {
		auto iter = fn1_map_.find(key);
		if (iter != fn1_map_.end()) {
			return iter->second;
		}
		return nullptr;
	}

	fn1_t get_fn1(const std::string& key1, const std::string& key2) {
		auto iter = fn1_map2_.find({key1, key2});
		if (iter != fn1_map2_.end()) {
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

	void call_fn1(const std::string& key1, const std::string& key2) {
		fn1_t func = get_fn1(key1, key2);
		if (func != nullptr) {
			func();
		} else {
			std::cerr << "Error: Function '" << key1 << ", " << key2 << "' not found!" << std::endl;
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
	funcMap.register_fn1("foo1.3", "key2", foo1);

	funcMap.call_fn1("foo1.1");
	funcMap.call_fn1("__not_exist__");
	funcMap.call_fn1("foo1.3", "key2");
	funcMap.call_fn1("foo1.3", "__not_exist__");

	return 0;
}
