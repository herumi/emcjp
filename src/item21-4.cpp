#include <stdio.h>
#include <vector>
#include <memory>
#include <iostream>
template<class T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args) {
  return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

template<class T>
void put(const T& v)
{
	std::cout << "size=" << v.size();
	for (const auto& x : v) {
		std::cout << ", " << x;
	}
	std::cout << std::endl;
}

using Vec = std::vector<int>;

int main()
{
	auto pv1 = make_unique<Vec>(10, 20);
	put(*pv1);
//	auto pv2 = make_unique<Vec>({10, 20}); // error
	auto il = {10, 20};
	auto pv3 = make_unique<Vec>(il); // error
	put(*pv3);
}
