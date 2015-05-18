#include <stdio.h>
#include <new>
#include <memory>

struct A {
	A() { puts("A cstr"); }
	~A() { puts("A dstr"); }
};

struct B {
	B() { puts("B cstr"); throw std::bad_alloc(); }
	~B() { puts("B dstr"); }
};

struct C {
	C() : a(new A()) , b(new B()) { }
	~C()
	{
		delete a;
		delete b;
	}
	A *a;
	B *b;
};

#ifdef USE_MAKE_UNIQUE

struct D {
	D() : a(new A()) , b(new B()) { }
	std::unique_ptr<A> a;
	std::unique_ptr<B> b;
};
#endif

int main()
	try
{
#ifdef USE_MAKE_UNIQUE
	D d;
#else
	C c;
#endif
} catch (std::exception& e) {
	printf("ERR %s\n", e.what());
}
