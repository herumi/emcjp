# Effective Modern C++勉強会


## 資料置き場

### [本家eratta](http://www.aristeia.com/BookErrata/emc++-errata.html)

### [第1回 2015/1/28](https://atnd.org/events/60511)

* [Item 1, 2の資料](http://www.slideshare.net/herumi/template-44013078) : [@herumi](https://twitter.com/herumi)
* [Item 3, 4の資料](http://www.slideshare.net/starpos/effective-modern-c-1-item34) : [@starpoz](https://twitter.com/starpoz)
* [Item 5, 6の資料](http://www.slideshare.net/taka111/emcpp0506) : [@redboltz](https://twitter.com/redboltz)

### [第2回 2015/2/25](https://atnd.org/events/62014)

* Item 7, 8 : [@Talos208](https://twitter.com/Talos208)
* [Item 9, 10の資料](http://www.slideshare.net/uchan_nos/effective-modern-c-2pptx) : [@uchan_nos](https://twitter.com/uchan_nos)
* [Item 11の資料](http://www.slideshare.net/KeisukeFukuda/effective-modern-c2-item1011) : [@keisukefukuda](https://twitter.com/keisukefukuda)

### [第3回 2015/3/25](https://atnd.org/events/63259)

* [Item 12の資料](http://www.slideshare.net/KeisukeFukuda/effective-modern-c-3) : [@keisukefukuda](https://twitter.com/keisukefukuda)
    - [blog](http://freak-da.hatenablog.com/entries/2015/03/26)
* Item 13, 14 : [@pepshiso](https://twitter.com/pepshiso)
* Item 15 : [@kariya_mitsuru](https://twitter.com/kariya_mitsuru)

### [第4回 2015/4/22](https://atnd.org/events/64371)

* Item 16 [@kariya_mitsuru](https://twitter.com/kariya_mitsuru)
* [Item 17, 18の資料](http://www.slideshare.net/rigarash/effective-modern-c4-item-17-18) : [@rigarash](https://twitter.com/rigarash)
* [Item 19, 20の資料](https://speakerdeck.com/rhysd/effective-modern-c-plus-plus-item19-item20) : [@linda_pp](https://twitter.com/linda_pp)

### [第5回 2015/5/20](https://atnd.org/events/65442)

* [Item 21の資料](http://www.slideshare.net/herumi/emcjp-item21) [@herumi](https://twitter.com/herumi)
* [Item 22の資料](http://www.slideshare.net/KeisukeFukuda/effective-modern-c-item-22) [@keisukefukuda](https://twitter.com/keisukefukuda)
* [Item 23の資料](http://www.slideshare.net/uchan_nos/effective-modern-c-5) [@uchan_nos](https://twitter.com/uchan_nos)
* [Item 24の資料](http://www.slideshare.net/mooopan/emc24) [@mooopan](https://twitter.com/mooopan)

### [第6回 2015/6/17](https://atnd.org/events/66415)

* Item 25 [@starpoz](https://twitter.com/starpoz)
* [Item 26の資料](http://www.slideshare.net/barfoo102/emc-26) [@regenschauer490](https://twitter.com/regenschauer490)
* Item 27 [@kariya_mitsuru](https://twitter.com/kariya_mitsuru)
* Item 28 [@redboltz](https://twitter.com/redboltz)

### [第7回 2015/7/15](https://atnd.org/events/67443)

* Item 29, 30 : [@Linda_pp](https://twitter.com/Linda_pp)
* Item 31 : [@MitsutakaTakeda](https://twitter.com/MitsutakaTakeda)
* Item 32 : [@simizut22](https://twitter.com/simizut22)
* Item 33 : [@herumi](https://twitter.com/herumi)

### 疑問やコメントなど(随時思い出したら書く)

### 以前

[memo.md](memo.md)

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
