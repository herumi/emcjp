/*
cl item21-3.cpp /MT

           /DUSE_MAKE_SHARED
0 40       0 40
1 5781     1 5781
2 552      2 552
3 29       3 29
4 4096     4 4096
5 16   ;   5 32   ;
6 24   ;   6 32   ;
7 16   ;   7 32   ;
8 24   ;
9 16   ;
10 24  ;

gcc

0 16   ;  0 40
1 24   ;  1 40
2 16   ;  2 40
3 24
4 16
5 24
*/
#include <memory>
#include <stdio.h>
#include <stdlib.h>

static int pos = 0;
static struct Mmem {
	char buf[8192];
	size_t size;
} mem[4096];

extern "C" void *malloc(size_t n) throw()
{
	if (n >= 8192) {
		puts("ERR");
		exit(1);
	}
	mem[pos].size = n;
	return mem[pos++].buf;
}
extern "C" void free(void *p) throw()
{
	if (p == 0) return;
	printf("free %p\n", p);
}

struct A {
	int a[4];
};

void f()
{
#ifdef USE_MAKE_SHARED
	auto p = std::make_shared<A>();
#else
	std::shared_ptr<A> p(new A());
#endif
}

int main()
{
	for (int i = 0; i < 3; i++) {
		f();
	}
	for (int i = 0; i < pos; i++) {
		printf("%d %d\n", i, (int)mem[i].size);
	}
}
