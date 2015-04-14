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

auto delA0 = [](A* p) {
	printf("delA0 %p\n", p);
	delete p;
};

void delA1(A* p)
{
	printf("delA1 %p\n", p);
	delete p;
}

int main()
{
	std::unique_ptr<A, decltype(delA0)> p(new A(), delA0);
	std::unique_ptr<A, decltype(delA0)> q(nullptr, delA0);
	q.reset(new B());
	printf("sizeof p=%d\n", (int)sizeof(p)); // 8
	std::unique_ptr<A, void (*)(A*)> r(new A(), delA1);
	printf("sizeof r=%d\n", (int)sizeof(r)); // 16
}
