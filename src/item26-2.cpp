#include <string>
#include <stdio.h>
#include <type_traits>

struct B {
	template<class T, class = typename std::enable_if<!std::is_same<B, typename std::decay<T>::type>::value>::type>
	explicit B(T&& s)
		: s(std::forward<T>(s))
	{
		puts("forward");
	}
	B(int) { puts("int"); }
	B(short) { puts("short"); }
	std::string s;
};

int main()
{
	B b1("abc");
	B b2(3);
	short i = 4;
	B b3(i);
	B b4(b1);
}