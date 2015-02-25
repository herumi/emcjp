#include <stdio.h>
#include <vector>

template<class T, typename... Ts>
void func1(Ts&&... params) {
    T v(std::forward<Ts>(params)...);
    for (auto x : v) {
        printf("%d\n", x);
    }
}

template<class T, class... Ts>
void func2(Ts&&... params) {
    T v{std::forward<Ts>(params)...};
    for (auto x : v) {
        printf("%d\n", x);
    }
}

int main()
{
    using Vec = std::vector<int>;
    puts("A");
    func1<Vec>(10, 1); // 10 elements of 1
    puts("B");
    func2<Vec>(10, 1); // two elements of 10, 1
}