#include <stdio.h>
#include <memory>

struct A {
	A() { puts("A cstr"); }
	~A() { puts("A dstr"); }
	std::shared_ptr<A> p;
};

struct B {
	B() { puts("B cstr"); }
	~B() { puts("B dstr"); }
	std::weak_ptr<B> p;
};

int main()
{
	// leak
	{
		auto s = std::make_shared<A>();
		auto t = std::make_shared<A>();
		s->p = t;
		t->p = s;
	}
	// not leak
	{
		auto s = std::make_shared<B>();
		auto t = std::make_shared<B>();
		s->p = t;
		t->p = s;
	}
}
