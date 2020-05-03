# for范围的小例子

我们很方便的使用

```
for(auto ch: classa)
{
	....
}
```

只要我们提供了`begin,end`以及迭代器类型的判断语句即可

[概念解释](https://zh.cppreference.com/w/cpp/language/range-for)

自己写的小例子

```cpp
#include <iostream>
using namespace std;
// https://zh.cppreference.com/w/cpp/language/range-for
class Dog
{

public:
    int v[100];
    int curr = 0;
    int *begin() { return &v[0]; }
    int *end() { return &v[99]; }
};

int main(int argc, char const *argv[])
{
    Dog v;
    for (int i = 0; i < 99; i++)
        v.v[i] = i;
    // for (auto c = v.begin(); c != v.end(); c++)
    // {
    //     std::cout << *c << std::endl;
    // }
    for (auto c : v)
        std::cout << c << std::endl;

    while (1)
        ;
    return 0;
}

```

