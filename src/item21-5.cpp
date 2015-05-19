#include <stdio.h>
#include <stdlib.h>
#include <memory>

struct A {
	int x[4];
	static inline void* operator new(size_t size)
	{
		printf("new size=%d\n", (int)size);
		return malloc(size);
	}
	static inline void operator delete(void* p)
	{
		printf("free\n");
		free(p);
	}
};

int main()
{
	{
		puts("new");
		A *p = new A();
		delete p;
	}
	{
		puts("shared_ptr");
		auto p = std::shared_ptr<A>(new A());
	}
	{
		puts("make_shared");
		auto p = std::make_shared<A>();
	}
}
