#### 結果
勉強会の中で出席者より質問のあった↑件、Scottに問い合わせ、本の内容に誤りがあったとの回答を得ました。errataにも掲載されました。

http://www.aristeia.com/BookErrata/emc++-errata.html
!  1/30/15 txk PDF      12
The third paragraph (beginning with "These examples all show lvalue reference  parameters, but type deduction works exactly the same way for rvalue reference parameters") should be removed. When the type of param in the template f on page 11 is changed to an rvalue reference (i.e., to have type "T&&"), it becomes a universal reference, and then the rules for Case 2 (on pages 13-14) apply.

#### 経緯
Scottからメール掲載許可を得たので、今後の参考のためにもここに転載しておきます。

##### 私→Scott

```
Hi Soctt,

This question is about 2015-01-20: Third Release.

Item1 page 12, there is the following paragraph:
-----
These examples all show lvalue reference parameters, but type deduction works
exactly the same way for rvalue reference parameters. Of course, only
rvalue arguments
may be passed to rvalue reference parameters, but that restriction has nothing
to do with type deduction.
-----

That doesn't make sense for me.
My first question is what these examples are. I think the examples are
written in the previous page, page 11:

template<typename T>
void f(T& param);  // param is a reference

int x = 27;        // x is an int
const int cx = x;  // cx is a const int
const int& rx = x; // rx is a reference to x as a const int

f(x);   // T is int, param's type is int&
f(cx);  // T is const int,
        // param's type is const int&
f(rx);  // T is const int,
        // param's type is const int&

You wrote "type deduction works exactly the same way for rvalue
reference parameters."
My second question is why you wrote about rvalue reference parameters
at this point. The rvalue reference parameters is not universal
reference parameters. Do you mean non template rvalue reference
parameters such as int&&? or non deduced template parameters with &&?
Anyway, I don't make sense why you wrote about that at this point.

My friends and I held the study group of EMC++ in Japan. It's so fun:)
One of atendee has the question above. I read again item1 carefully.
But I don't get the answer.

Thanks
Takatoshi
```

##### Scott→私

```
|    This question is about 2015-01-20: Third Release.
|
|    Item1 page 12, there is the following paragraph:
|    -----
|    These examples all show lvalue reference parameters, but type
|    deduction works
|    exactly the same way for rvalue reference parameters. Of course, only
|    rvalue arguments
|    may be passed to rvalue reference parameters, but that restriction has
|    nothing
|    to do with type deduction.
|    -----

[...]

|    Anyway, I don't make sense why you wrote about that at this point.
|
|    My friends and I held the study group of EMC++ in Japan. It's so fun:)
|    One of atendee has the question above. I read again item1 carefully.
|    But I don't get the answer.

That's because what I wrote is completely wrong, and I'm very glad that you brought this to my attention. I just added the following errata entry for page 12 to the book's errata page (http://www.aristeia.com/BookErrata/emc++-errata.html ):

    The third paragraph (beginning with "These examples all
    show lvalue reference  parameters, but type deduction
    works exactly the same way for rvalue reference
    parameters") should be removed. When the type of param
    in the template f on page 11 is changed to an rvalue
    reference (i.e., to have type "T&&"), it becomes a
    universal reference, and then the rules for Case 2
    (on pages 13-14) apply.

I apologize for this error in the book. I'll fix it when I next get a chance to make revisions.

Thanks again to you and your colleague for reporting this issue.



Scott
```

##### 私→Scott

```
Hi Scott,

Thank you for the reply. I understood it clearly now. Can I forward
this email to the members of study group? I believe that they would be
glad to hear your reply.

Here are the members of the study group:
https://atnd.org/events/60511

Thanks
Takatoshi
```

##### Scott→私

```
|    Thank you for the reply. I understood it clearly now. Can I forward
|    this email to the members of study group? I believe that they would be
|    glad to hear your reply.

Of course.

|    Here are the members of the study group:
|    https://atnd.org/events/60511

Thanks for this link.

Scott
```

