#include <initializer_list>

struct W {
  W(int, bool){}
  W(int, double){}
  W(std::initializer_list<bool>){}
};

int main()
{
  W w{10, 5.0}; // error
}

