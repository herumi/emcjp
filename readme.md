# Effective Modern C++勉強会


## 資料置き場

### [本家eratta](http://www.aristeia.com/BookErrata/emc++-errata.html)

### [第1回 2015/1/28](https://atnd.org/events/60511)

* Item 1, 2 : [@herumi](https://twitter.com/herumi), [templateとautoの型推論](http://www.slideshare.net/herumi/template-44013078)
* Item 3, 4 : [@starpoz](https://twitter.com/starpoz), [Item 3, 4](http://www.slideshare.net/starpos/effective-modern-c-1-item34)
* Item 5, 6 : [@redboltz](https://twitter.com/redboltz), [Item 5, 6](http://www.slideshare.net/taka111/emcpp0506)

### [第2回 2015/2/25](https://atnd.org/events/62014)

* Item 7, 8 : [@Talos208](https://twitter.com/Talos208)
* Item 9, 10 : [@uchan_nos](https://twitter.com/uchan_nos), [Item 9, 10](http://www.slideshare.net/uchan_nos/effective-modern-c-2pptx)
* Item 11, 12 : [@keisukefukuda](https://twitter.com/keisukefukuda), [Item 11, 12](http://www.slideshare.net/KeisukeFukuda/effective-modern-c2-item1011)

### 疑問やコメントなど(随時思い出したら書く)

### Item 1 p.12の

>These examples all show lvalue reference parameters, but
>type deduction works exactly the same way for rvalue reference parameters.

の意味が分からない。[テキストの間違い](misc/mail.md)

### Item 2のauto a{3}がinitializer_listになるのは気持ち悪い。

C++17で仕様変更された(by [@pepshiso](https://twitter.com/pepshiso/status/560384555257851904))。
[New Rules for auto deduction from braced-init-list](http://www.open-std.org/JTC1/SC22/WG21/docs/papers/2014/n3922.html)

```
                 // C++11, C++14    C++17
auto x = {1};    // 初期化リスト    初期化リスト
auto x = {1, 2}; // 初期化リスト    初期化リスト
auto x{1};       // 初期化リスト    int
auto x{1, 2};    // 初期化リスト    error
```

### Item 3のdecltype(x)とdecltype((x))で意味が変わる例

```
// C++14 only
decltype(auto) f2()
{
    static int x = 0;
    return (x); // ここをreturn xにするとコンパイルエラーになる。
}

int main()
{
    printf("f2()=%d\n", f2());
    f2() = 3;
    printf("f2()=%d\n", f2());
}
```

### Item 6のvector<bool>のoperatorをautoで受けると駄目な話。

[item6-1.cpp](https://github.com/herumi/emcjp/blob/master/src/item6-1.cpp)
VecがintではなくRefを返す。
intで受けるとRef()からintに変換されてから一時オブジェクトのVecとRefが消滅する。

autoで受けるとRef()のままになり、Refの寿命はあるけどそれが参照しているVecは先に消滅するのでそのあとintに変換するとアウト。
```
use int
Vec cstr
Ref cstr
read x
Ref dstr
Vec dstr
type=int a=5
use auto
Vec cstr
Ref cstr
Vec dstr
read x
type=struct Ref a=5
Ref dstr
```

### std::vector<T>::size_typeはsize_tで受けてよいのか?

問題になるとは思えないがどこかで保証してる?
