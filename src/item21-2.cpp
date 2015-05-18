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
template<class T, class... Args>
std::unique_ptr<T> make_unique(Args&&... args) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

struct D {
	D() : a(make_unique<A>()) , b(make_unique<B>()) { }
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
