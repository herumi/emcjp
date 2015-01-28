/*
	Item 6. bad use of auto
*/
#include <stdio.h>
#include <typeinfo>

struct Ref {
	int& x;
	Ref(int& x) : x(x) { puts("Ref cstr"); }
	~Ref() { puts("Ref dstr"); }
	operator int() { puts("read x"); return x; }
};

struct Vec {
	int x;
	Vec() : x(5) { puts("Vec cstr"); }
	~Vec() { puts("Vec dstr"); }
	Ref get() { return Ref(x); }
};

Vec createVec() { return Vec(); }

/*
use int
Vec cstr
Ref cstr
read x
Ref dstr
Vec dstr
type=int a=5

use auto
Vec cstr
Ref cstr
Vec dstr
read x
type=struct Ref a=5
Ref dstr
*/
int main()
{
	puts("use int");
	{
		int a = createVec().get();
		printf("type=%s a=%d\n", typeid(a).name(), a);
	}
	puts("");
	puts("use auto");
	{
		auto a = createVec().get();
		// access after calling destructor of Vec
		printf("type=%s a=%d\n", typeid(a).name(), (int)a);
	}
}
