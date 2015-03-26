# Effective Modern C++勉強会


## 資料置き場

### [本家eratta](http://www.aristeia.com/BookErrata/emc++-errata.html)

### [第1回 2015/1/28](https://atnd.org/events/60511)

* [Item 1, 2](http://www.slideshare.net/herumi/template-44013078) : [@herumi](https://twitter.com/herumi)
* [Item 3, 4](http://www.slideshare.net/starpos/effective-modern-c-1-item34) : [@starpoz](https://twitter.com/starpoz)
* [Item 5, 6](http://www.slideshare.net/taka111/emcpp0506) : [@redboltz](https://twitter.com/redboltz)

### [第2回 2015/2/25](https://atnd.org/events/62014)

* Item 7, 8 : [@Talos208](https://twitter.com/Talos208)
* [Item 9, 10](http://www.slideshare.net/uchan_nos/effective-modern-c-2pptx) : [@uchan_nos](https://twitter.com/uchan_nos)
* [Item 11](http://www.slideshare.net/KeisukeFukuda/effective-modern-c2-item1011) : [@keisukefukuda](https://twitter.com/keisukefukuda)

### [第3回 2015/3/25](https://atnd.org/events/63259)

* [Item 12](http://www.slideshare.net/KeisukeFukuda/effective-modern-c-3) : [@keisukefukuda](https://twitter.com/keisukefukuda)
* Item 13, 14 : [@pepshiso](https://twitter.com/pepshiso)
* Item 15 : [@kariya_mitsuru](https://twitter.com/kariya_mitsuru)

### [第4回 2015/4/22](https://atnd.org/events/63259)

* Item 16 [@kariya_mitsuru](https://twitter.com/kariya_mitsuru)
* Item 17, 18 : [@rigarash](https://twitter.com/rigarash)
* Item 19, 20 : [@linda_pp](https://twitter.com/linda_pp)

### 疑問やコメントなど(随時思い出したら書く)

### 以前

[memo.md](memo.md)

### Item 12
override使う。
gccでは-Wall, -Wextraの他に-Woverloaded-vitrualが必要

メンバ関数のreference qualifierのメリットの例

`a + b = 3`を防げる。
```
struct X {
    friend inline X operator+(const X&, const X&) { return X(); }
    X& operator=(int) { return *this; }
    X& operator=(const char*) & { return *this; }
};

int main()
{
    X a, b;
    a + b = 3;   // 通ってしまう
    a + b = "a"; // &がついてるとエラーにできる
}
```

reference qualifierをつけまくったときでgccがambigiousでエラーになるのは4.9.1から直ってました。
[item12-1.cpp](src/item12-1.cpp)

### Item 13
C++03はconst_iteratorは冷遇されていた。C++11からはcbegin, cendを使う。
C++14からはグローバル関数のcbegin, cendを使う。
### Item 14
スタックの巻き戻しに必要なコードを減らせるため可能ならthrow()よりもnoexceptを使う。
```
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

int main()
{
#ifdef NOEXCEPT
    puts("noexcept");
    f_noexcept();
#else
    puts("throw()");
    f_nothrow();
#endif
}
```
throw()版なら
```
terminate called after throwing an instance of 'int'

noexcept
cstr
dstr
```
dstrが呼ばれてからstd::unexpected()が呼ばれ、それがstd::terminate()になっている。
noexceptならdstrを呼ばずに即座にstd::terminate()を呼ぶ。
```
terminate called after throwing an instance of 'int'

noexcept
cstr
```
ただし今のところこの最適化はgccのみ。clang(-3.7)では変わらない。

### Item 15
* 可能ならconstexprを使え。
* メンバ関数のconstexprにはconstもつけること(C++14で挙動が変わる)。
* setterにconstexprをつけるとよいことがある。

```
#include <utility>
#include <stdio.h>

struct A {
    static constexpr std::pair<int,int> p{3,5};
};

int main()
{
    printf("A::p.first=%d\n", A::p.first);
}
```
がgccでエラーになるのはバグ? コードが悪い?
=> 多分バグ
