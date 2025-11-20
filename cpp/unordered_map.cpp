#include <iostream>
#include <unordered_map>

typedef void (*fn1_t)(void);
typedef void (*fn2_t)(void);

#define FUNC_DEBUG()	std::cout << "Calling " << __func__ << ": " << __LINE__ << std::endl;

class func_map {
private:
	struct PairHash {
		size_t operator()(const std::pair<std::string, std::string>& key) const noexcept {
			size_t hash1 = std::hash<std::string>{}(key.first);
			size_t hash2 = std::hash<std::string>{}(key.second);
			auto hash_combine = [](size_t seed, size_t val) {
				seed ^= val + 0x9e3779b9 + (seed << 6) + (seed >> 2);
			};
			hash_combine(hash1, hash2);
			return hash1;
		}
	};
	struct PairEqual {
		bool operator()(const std::pair<std::string, std::string>& lhs,
			 const std::pair<std::string, std::string>& rhs) const noexcept {
			return lhs.first == rhs.first && lhs.second == rhs.second;
		}
	};
	std::string makeKey(const std::string& key1, const std::string& key2) const {
		return key1 + '\0' + key2;
	}
	std::unordered_map<std::string, fn1_t> fn1_map_;
	std::unordered_map<std::pair<std::string, std::string>, fn1_t, PairHash, PairEqual> fn1_map2_;
	std::unordered_map<std::string, fn2_t> fn2_map_;
public:
	func_map() {
	}
	virtual ~func_map() = default;

	void register_fn1(const std::string& key, fn1_t func) {
		fn1_map_[key] = func;
	}
	void register_fn1(const std::string& key1, const std::string& key2, fn1_t func) {
		fn1_map2_[{key1, key2}] = func;
	}
	void register_fn2(const std::string& key1, const std::string& key2, fn2_t func) {
		fn2_map_[makeKey(key1, key2)] = func;
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

	fn2_t get_fn2(const std::string& key1, const std::string& key2) {
		auto iter = fn2_map_.find(makeKey(key1, key2));
		if (iter != fn2_map_.end()) {
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

	void call_fn2(const std::string& key1, const std::string& key2) {
		fn2_t func = get_fn2(key1, key2);
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
	funcMap.register_fn2("foo1.4", "key2", foo1);

	funcMap.call_fn1("foo1.1");
	funcMap.call_fn1("__not_exist__");
	funcMap.call_fn1("foo1.3", "key2");
	funcMap.call_fn1("foo1.3", "__not_exist__");
	funcMap.call_fn2("foo1.4", "key2");
	funcMap.call_fn2("foo1.4", "__not_exist__");

	return 0;
}
