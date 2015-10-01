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

### Item 7

* `{}`のメリット
    * 適用可能なケースが多い
    * 間違えてnarrowingしてしまう可能性が低い
    * Most Vexing Parse(変数宣言が関数のプロトタイプになってしまうやつ)の心配がない
* `()`のメリット
    * C++98の文法と互換
    * initializer_listに関する問題がない

templateの中で一次オブジェクトを作るとき、`{}`と`()`のどちらを使っているかドキュメントに書かないと利用する人はわからないことがある。
[item7-3.cpp](https://github.com/herumi/emcjp/blob/master/src/item7-3.cpp)

### Item 8
整数型とポインタのオーバーロードは止めよう

### Item 9

typedef vs. using
* usingはtemplate化が可能。使うときは`typename`は要らない。`::type`も要らない。
    * typedefのときはdependent type
    * usingはnon-dependent type
    * C++14ではremove_constなどに_tバージョンが追加された。
    * [本家eratta 1/25/15 tyk All](http://www.aristeia.com/BookErrata/emc++-errata.html)にtypedefよりalias templateがよい例が載ってる。

Q. alias templateは特殊化できないけどどうなんだ。→ templateクラスのラップ
* 元のクラスの特殊化と区別できないからしかたない?
* 使う人からするとそんなことを気にせず特殊化したい?

### Item 10
enum Class使え。

Visual Studioでは
```
enum X {
   x = 1234567890123ull
};
```
は32bitを超えた部分が切り捨てられる。
```
enum class X:long long {
    x = 1234567890123ull
};
```
ならOK。

### Item 11
* 代入演算子を使えなくするにはprivateじゃなくて`= delete`の方がいい。
* `= delete`はprivateじゃなくてpublicに書く方がいい。
    * コンパイラはdeletedかどうかより先にaccessibilityをチェックするため。

普通の関数でも`= delete`は使える。
templateでdefault deleteにして使いたいのだけ特殊化、あるいはオーバーロードする。
```
#include <stdio.h>
template <typename T>
void f(T) = delete;

void f(int) { puts("int"); }

int main()
{
    f(3);
    f('a'); // deleteがないとintにmatchしてしまう。
}

```
* char32_tなどは予約語なので`std::`は要らない(erattaに連絡済み)。

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

### Item 19
共有リソースの管理にはshared_ptrを使う。
[Cryoliteさんの昔の解説記事](http://d.hatena.ne.jp/Cryolite/20060108)
* すぐ戻ってくる関数で使うならcopyよりmoveの方が参照カウンタが増えないのでいい。
* shared_ptrで確保したインスタンスのthisを別のshared_ptrに渡してはいけない。
    - enable_shared_from_thisを継承してshared_from_thisを使う。

### Item 20
ちゅうぶらりん(dangling)になるかもしれないshared_ptrに対してはweak_ptrを使う。

```
auto s = std::make_shared<A>();
std::weak_ptr<A> w(s);

if (w.expired()) {
  ... /// XXX
}
```
この方法だとw.expired()がtrueでもXXXの時点で
sが他のスレッドで解放されてfalseになってるかもしれないので使うべきではない。

```
if (auto p = w.lock()) {
  ...
}
```
の形だとshared_ptrへの変換と判定がatomicに行われるのでよい。

### Item 21

unique_ptrやshared_ptrよりはmake_unique(from C++14)やmake_sharedを使おう。
ただしmake_sharedはいろいろ罠があるので気をつける。
make_shared<T>を使うとT::operator newが呼ばれないのはもっと明記した方がよいような。

Q. use_count()の戻り値がsize_tではなくlongなのはなぜ? boostのときからそうだけど。

### Item 16
constメンバ関数はthread safeにすべき。

### Item 17
特殊なメンバ関数の自動生成を理解する。
moveされることを期待するならちゃんと書く。
自明なdstrを定義すると暗黙のmoveはcopyになってしまうので注意する。
### Item 18
auto_ptrの代わりにunique_ptrを使う。
カスタムdeleterは関数よりlambdaの方が効率がよい。

* Q. socketやfile descriptorなどはポインタ型でないのでshared_ptrとか使いにくい。
* A. see [Resource Management with Explicit Template Specializations](http://accu.org/index.php/journals/2086)

### Item 22
pImplの実装にunique_ptrを使う。
cppに特殊メンバ関数をきちんと書かなければならない。
pImplがnullptrになっているとき(自分自身もrhsも)を考慮したcopy cstrやoperator=を書く必要がある。

たとえば
```
std::string a = "abc";
std::string b(std::move(a));
```
したとき、`a.c_str()`の値は未規定(unspecified)ではあるが、`valid state`ではあるのでsegvしてはいけない。
valid stateってなんだよという疑問はあるが。
本は間違ってるので注意(最新版pdfでは修正されているらしい)。
たとえばこんな感じ。
```
class A {
    ....
private:
    struct Impl;
    std::unique_ptr<Impl> pImpl_;
};

A::A(const A& rhs)
    : pImpl_(std::unique_ptr<Impl>(rhs.pImpl_ ? new Impl(*rhs.pImpl_) : new Impl()))
{
}

A& A::operator=(const A& rhs)
{
    if (rhs.pImpl_) {
        if (pImpl_) {
            *pImpl_ = *rhs.pImpl_;
        } else {
            pImpl_.reset(new Impl(*rhs.pImpl_));
        }
    } else {
        pImpl_.reset();
    }
    return *this;
}
```
そのあたりはmake_sharedを使うと楽になるよと書いてあるが、make_sharedを使うとインスタンスは共有されるので元のクラスの意味と違ってしまうので要注意(こちらも最新pdfでは記載されているらしい)。

### Item 23

std::moveやstd::forwardは単なるremove_reference_t<T>&&へのキャスト。
std::moveはTの型を明示しなくてよいがstd::forwardは明示する必要がある。

Q. std::moveをconst T&&に対してエラーするのはどうか。

### Item 24
template<class T>void f(T&& param)やauto&&などの型推論が行われるところでのみ
T&&は右辺値にも左辺値にも束縛される可能性がある。
* lvalueで初期化するとlvalue referenceになる。
* rvalueで初期化するとrvalue referenceになる。
著者はuniversal referenceという言葉を推している。

### Item 25
右辺値参照にはstd::move, universal参照にはstd::forwardを使う。
* moveのほうが短くてよいけどしてほしくないときにmoveされてしまうことがある。
```
struct A {
	template<class T>
	void set(T&& rhs)
	{
		a = std::move<T>(rhs);
	}
	std::string a;
};
std::string getName() { return "abc"; }
```
```
A a;
std::string n = getName();
a.set(n);
// nの値は不明。
```

```
A f(A a) {
   return a;
}
```
はRVO, NRVOではないがstd::moveされる。

Q. `A operator+(A&& lhs, const A&& rhs)`でAを返すのは何故?
A. a + b + cみたいにしたいから。std::stringのoperator+はいろんなパターンのオーバーロードで頑張ってる。

### Item 26
universal参照のoverloadを避ける。
```
struct A {
   void set(const std::string& a) { this->a = a; }
   std::string a;
};
```
set("abc"), set(std::string("abc"))などで効率がよくない。

```
struct A {
   template<class T>
   void set(T&& a) { this->a = std::forward<T>(a); }
   std::string a;
};
```
なら効率がよい。
しかしset(int idx)を追加すると`short a; set(a)`がコンパイルエラー。

オーバーロードのマッチの優先順位
1. 非関数templateで引数が一番マッチする
2. 関数templateでtemplate argument deductionで1と同じシグネチャにマッチする
3. 暗黙の型変換でマッチする

コンストラクタが困ってしまう。

* 値"abc"に変数(name)を束縛する(bind)。逆に言い間違えやすい。

### Item 27
universal ref以外のオーバーロード

メモ書き

* univresal refは知らないとトラブルになりやすい。思った通りに動いてくれば問題ない。

解決法

1. overloadを諦める。

* 名前を変えればよい。
* 欠点 : cstrには無力(名前が無い)。

2. const T&で渡す。

* 欠点:universal refほど効率的ではない。シンプルさは魅力的。

3. 値で渡す。

* 効率はわりといい。universal refほどではない。Item 41で。
* 欠点 : std::moveが効率悪いと駄目。
* 0はともかくNULLを渡すとintになる。

4. tag dispatch

* universal refの欠点
* 欠点 : あらゆるものにマッチする。
* universal refで引数を増やせばよい。
* Tがintとint以外で異なるものにdispatch
* 欠点 : cstrには無力

5. universal refをとるtemplateに制約を設ける

* 関数を呼ばれてほしいときだけ有効にする : std::enable_if ; SFNIAE
* 欠点 : エラーが読めない


こういう書き方もある。
```
#include <stdio.h>
#include <string>
#include <type_traits>

template<class T, typename std::enable_if<std::is_integral<T>::value>::type* = 0>
void f(T&&)
{
  puts("integral");
}

int main()
{
    f(3);
}
```

Q. シグネチャに戻り値を含むのだっけ。

A. http://stackoverflow.com/questions/290038/is-the-return-type-part-of-the-function-signature
普通の関数は、戻り値の型をシグネチャに含まない。関数テンプレートの特殊化は含む。

###Item 28
参照の畳み込み(collapsing)を理解する
畳み込みが起こる場所
* templateのinstantiation
* autoの型生成
* typedefとusing
* decltype
```
&  &  => &
&& &  => &
&  && => &
&& && => &&
```

### Item 29
std::moveがいつでもできて軽いというわけじゃないので気をつけよう。

VC2013がデフォルトのmove cstrを作らないので悲しい。VC2015は大丈夫。
### Item 30
perfect forwardingが失敗する例。

* 初期化リスト(non deduced context)。autoのときと同じ(item 2)
* ポインタとしての0やNULL
* static const data
```
#include <stdio.h>
#include <utility>

struct A {
    static const int a = 3;
};

void f(int x) { printf("%d\n", x); }

template<class T>
void fwd(T&& p) { f(std::forward<T>(p)); }

int main()
{
//  f(A::a);
    fwd(A::a);
}
```
これがリンクエラーになるので要注意(gcc -O0)。
```
const int A::a;
```
が必要。

### Item 31
[資料](http://www.slideshare.net/mitsutaka_takeda/emcpp-item31)が詳しいのでそちらを参照。
引数のキャプチャにはby-valueとby-referenceの二つがある。
変数の寿命に十分注意すること。

lambda式を定義と同時に呼び出すときは&でいいのではという案。
```
const auto size = [&]{ return condition ? 1 : 2; }();
```

Q. lambdaの中で使われなかった変数はコピーされる?

A. 実際に使われた変数のみがコピーされる. 明示した場合はコピーされる.
### Item 32
C++14ではキャプチャ時にmoveできるようになった。
```
auto func = [pw = std::move(pw)]{ pw->isValidate(); };
```
補足: gcc-5.xでは
```
auto func = [pw{std::move(pw}]{ pw->isValidate(); };
```
という書き方もできる。

C++11ではstd::bindを組み合わせればできる。

Q. でも一時的なものだったらクラスを明示的に作った方がわかりやすくていいんじゃないか?

### Item 33
C++14で導入されたgeneric lambda。
その中でstd::forwardしたいときはdecltypeを使う。
```
auto f = [](auto&& x) {
  return func(normalize(std::forward<decltype(x)>(x)));
}
```
### Item 34
* C++11で入ったstd::bindはC++14で入ったmoveキャプチャ可能なlambdaとgeneric lambdaのおかげで不要になった。
* std::bindを使うときは、bindするときに呼びたくない関数はbindを重ねる必要がある。
Meyersが間違えるぐらいにややこしいので使わない方が無難。
