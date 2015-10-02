# Effective Modern C++勉強会


## 資料置き場

### [本家errata](http://www.aristeia.com/BookErrata/emc++-errata.html)

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

* [Item 25の資料](http://www.slideshare.net/starpos/effective-modern-c-6-item25) [@starpoz](https://twitter.com/starpoz)
* [Item 26の資料](http://www.slideshare.net/barfoo102/emc-26) [@regenschauer490](https://twitter.com/regenschauer490)
* Item 27 [@kariya_mitsuru](https://twitter.com/kariya_mitsuru)
* Item 28 [@redboltz](https://twitter.com/redboltz)

### [第7回 2015/7/15](https://atnd.org/events/67443)

* [Item 29, 30の資料](https://speakerdeck.com/rhysd/effective-modern-c-plus-plus-du-shu-hui-item29-item30) : [@Linda_pp](https://twitter.com/Linda_pp)
* [Item 31の資料](http://www.slideshare.net/mitsutaka_takeda/emcpp-item31) : [@MitsutakaTakeda](https://twitter.com/MitsutakaTakeda)
* [Item 32の資料](http://www.slideshare.net/simizut22/emc-chapter32) : [@simizut22](https://twitter.com/simizut22)
* [Item 33, 34の資料](http://www.slideshare.net/herumi/emcjp-item3334) : [@herumi](https://twitter.com/herumi)

### [第8回 2015/8/19](https://atnd.org/events/68406)

* [Item 35の資料](http://www.slideshare.net/KeisukeFukuda/effective-modern-c-item-35) : [@keisukefukuda](https://twitter.com/keisukefukuda)
* [Item 36の資料](http://www.slideshare.net/simizut22/effective-modern-cchapeter36) : [@simizut22](https://twitter.com/simizut22)
* [Item 37の資料](http://www.slideshare.net/uchan_nos/effective-modern-c-8 ) : [@uchan_nos](https://twitter.com/uchan_nos)
* [Item 38の資料](http://www.slideshare.net/starpos/effective-modern-c-8-item38) : [@starpoz](https://twitter.com/starpoz)

### [第9回 2015/9/30](https://atnd.org/events/69460)

* Item 39 : [@redboltz](https://twitter.com/redboltz)
* [Item 40の資料](http://www.slideshare.net/simizut22/effective-modernc9) : [@simizut22](https://twitter.com/simizut22)
* [Item 41の資料](http://www.slideshare.net/mitsutaka_takeda/emcpp-item41) : [@MitsutakaTakeda](https://twitter.com/MitsutakaTakeda)
* [Item 42の資料](http://www.slideshare.net/herumi/emcjp-item-42) : [@herumi](https://twitter.com/herumi)

### 疑問やコメントなど(随時思い出したら書く)

[memo.md](memo.md)

### Item 39.

* ポーリングのtips
Intelにはbusy loopを検知してCPUパフォーマンスをあげて電力消費を減らすpause命令がある。

参考:[Benefitting Power and Performance Sleep Loops](https://software.intel.com/en-us/articles/benefitting-power-and-performance-sleep-loops)

* 条件変数のwaitは、イベントが本当に発生したらtrueを返すラムダ式と一緒に使うべき。
偽の起動(spurious wakeup)があるため。

参考:[条件変数とspurious wakeup](http://d.hatena.ne.jp/yohhoy/20120326/)

Q. vector<thread> vtにemplace_backしている途中で例外が発生したらset_valueするまえに抜けるのでブロックする可能性がある?

A. scope_exitをthreadを生成するループの前に置くとよいだろう。

### Item 40.
Q. intとかの整数型はいつでもlockでatomicを実現するの?

A. アーキテクチャによって違う。Intel系でも32bit環境でint64_tだと結構複雑。
VCだと`_InterlockedExchangeAdd64`, clangだと_atomic_fetch_add_8を呼ぶ。
gccだとinlineでlock cmpxchg8bとloopの組み合わせ.
```
.L2:
    movl    %eax, %ecx
    movl    %edx, %ebx
    addl    $1, %ecx
    adcl    $0, %ebx
    movl    %ebx, %ebp
    movl    %ecx, %ebx
    movl    %ebp, %ecx
    lock cmpxchg8b  (%esi)
    jne .L2
```

volatileの細かい仕様は各コンパイラの処理系依存。
規格上CとC++でも違う。以下雑多なメモ。
```
void f(int *nv1, int *nv2, volatile int *v)
{
    *nv1 = 1;
    *nv2 = 2;
    *v = 3;
    *nv2 = 4;
    *v = 5;
    *nv1 = 6;
}
```
VC, clangでは1, 2, 3, 4, 5, 6全ての書き込み命令がその順序で生成された。
```
// VC2015
mov DWORD PTR [rcx], 1
mov DWORD PTR [rdx], 2
mov DWORD PTR [r8], 3
mov DWORD PTR [rdx], 4
mov DWORD PTR [r8], 5
mov DWORD PTR [rcx], 6
```
```
// clang 3.5
movl    $1, (%rdi)
movl    $2, (%rsi)
movl    $3, (%rdx)
movl    $4, (%rsi)
movl    $5, (%rdx)
movl    $6, (%rdi)
```
gcc-4.8では1, 2の書き込みは消えた。
```
movl    $3, (%rdx)
movl    $4, (%rsi)
movl    $5, (%rdx)
movl    $6, (%rdi)
```

* [MSDN](https://msdn.microsoft.com/ja-jp/library/12a04hfd.aspx)
* [clang](http://llvm.org/docs/Atomics.html)
* [gcc](https://gcc.gnu.org/onlinedocs/gcc/Volatiles.html)
volatileの最低限の要件は、シーケンスポイントにおいてvolatile変数より前の全てのアクセスが完了し、後続するアクセスは起こらないこと。
シーケンスポイント間のvolatileアクセスの順序入れ替えや結合は許可されている。
シーケンスポイントを越えてのその操作はできない。

非volatileへのアクセスはvolatileへのアクセスに関して順序づけられない。
volatile変数を非volatileメモリへの書き込みの順序づけのためのメモリバリアには使えない。
```
int *ptr = something;
volatile int vobj;
*ptr = something;
vobj = 1;
```
vobjへの書き込みが起こるまでに*ptrへの書き込みがあることは保証されない。
```
int *ptr = something;
volatile int vobj;
*ptr = something;
asm volatile ("" : : : "memory");
vobj = 1;
```
しないといけない。

* [g++](https://gcc.gnu.org/onlinedocs/gcc/C_002b_002b-Volatiles.html)
```
void f(volatile int *v)
{
   *v;
}
```
C++的には*v;をlvalueからrvalueへの変換をしない。脱参照された型は不完全かもしれない。
その変換がメモリアクセスを引き起こすかどうかは明記しない。
しかし、それだと大抵のプログラマが驚くのでg++ではvolatileオブジェクトの脱参照はCと同じに扱う。
```
movl (%rdi), %eax ; アクセス発生
ret
```
VCも同様に残す。
clangはCでbuildすると残す。C++では残さない。
```
clang -x c -S -Ofast t.c
f:
    movl    (%rdi), %eax
    retq
```
```
clang -x c++ -S -Ofast t.c
f:
    retq
```
cf. シーケンスポイント
`&&`の左側, `||'の左側, コンマ演算子の左側, 関数の呼び出し, 条件演算子の最初のオペランド, 完全な初期化式の終わり, 式ステートメントの式,
if, switchないの制御式, while, doの制御式, forの3つの式, returnの式

# Item 41.
Q. shared_ptrなどはconst&で渡す?
A. 生ポインタを渡すこともある。あとconst shared_ptrはconstと紛らわしいのであまり使わないかも。
```
#include <stdio.h>
#include <memory>

struct A {
  A(int a) : a(a) { printf("cstr %d\n", a); }
  ~A() { printf("dstr %d\n", a); }
  int a;
};

void f(const std::shared_ptr<A>& a)
{
  a.get()->a = 5; // 書き換え可能
}

int main()
{
  std::shared_ptr<A> a = std::make_shared<A>(3);
  f(a);
}
```

＊ slideの最後に上げられている参考文献へのリンク
* [Keynote: The Evolving Search for Effective C++ by Scott Meyers](http://meetingcpp.com/index.php/tv14/items/23.html)
** Item 42のpush_backとemplace_backの話もでている。
* [Back to the Basics! Essentials of Modern C++ Style by Herb Sutter](https://isocpp.org/blog/2015/02/cppcon-2014-back-to-the-basics-essentials-of-modern-c-style-herb-sutter)
** cstrのみ値渡しという手法の提案
