#include <stdio.h>
#include <memory>

struct A {
	A() { puts("A cstr"); }
	virtual ~A() { puts("A dstr"); }
};

struct B : A {
	B() { puts("B cstr"); }
	~B() { puts("B dstr"); }
};

int main()
{
	auto delA = [](A* p) {
		printf("delete %p\n", p);
		delete p;
	};
	std::unique_ptr<A, decltype(delA)> p(new A(), delA);
	std::unique_ptr<A, decltype(delA)> q(nullptr, delA);
	q.reset(new B());
}
