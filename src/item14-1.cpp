#include <exception>
#include <stdio.h>

struct A {
    A() { puts("cstr"); }
    ~A() { puts("dstr"); }
};

void f_noexcept() noexcept {
    A a;
    throw 1;
}

void f_nothrow() throw() {
    A a;
    throw 1;
}

void putmsg()
{
    puts("putmsg is called");
}

int main()
{
    std::set_unexpected(putmsg);
#ifdef NOEXCEPT
    puts("noexcept");
    f_noexcept();
#else
    puts("throw()");
    f_nothrow();
#endif
}