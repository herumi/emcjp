#include <stdio.h>

struct X {
    X(){}
    void f() & { puts("1 f &"); }
    void f() && { puts("2 f &&"); }
    void f() const & { puts("3 f c&"); }
    void f() const && { puts("4 f c&&"); }
    void f() volatile & { puts("5 f v&"); }
    void f() volatile && { puts("6 f v&&"); }
    void f() const volatile & { puts("7 f cv&"); }
    void f() const volatile && { puts("8 f cv&&"); }
};

int main()
{
    X x;
    const X cx;
    volatile X vx;
    const volatile X cvx;
    x.f();
    X().f();
    cx.f();
    static_cast<const X&&>(X()).f();
    vx.f();
    static_cast<volatile X&&>(X()).f();
    cvx.f();
    static_cast<const volatile X&&>(X()).f();
}
/*
1 f &
2 f &&
3 f c&
4 f c&&
5 f v&
6 f v&&
7 f cv&
8 f cv&&
*/
