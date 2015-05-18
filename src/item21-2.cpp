#include <stdio.h>
#include <new>

struct A {
	A() { puts("A cstr"); }
	~A() { puts("A dstr"); }
};

struct B {
	B() { puts("B cstr"); throw std::bad_alloc(); }
	~B() { puts("B dstr"); }
};

struct C {
	C()
		: a(new A())
		, b(new B())
	{
	}
	~C()
	{
		delete a;
		delete b;
	}
	A *a;
	B *b;
};

int main()
	try
{
	C c;
} catch (std::exception& e) {
	printf("ERR %s\n", e.what());
}
