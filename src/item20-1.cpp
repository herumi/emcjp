#include <stdio.h>
#include <memory>

struct A {
	int a;
	A(int a) : a(a) { puts("cstr"); }
	~A() { puts("dstr"); }
	void put() const { printf("a=%d\n", a); }
};

void testAndPut(const std::weak_ptr<A>& w)
{
	puts("testAndPut");
	if (auto p = w.lock()) {
		p->put();
	} else {
		puts("none");
	}
}

int main()
{
	auto s = std::make_shared<A>(3);
	s->put();
	std::weak_ptr<A> w = s;
	testAndPut(w);
	puts("s.reset()");
	s.reset();
	testAndPut(w);
	puts("s.reset(new A(5))");
	s.reset(new A(5));
	testAndPut(w);
	w = s;
	testAndPut(w);
}
