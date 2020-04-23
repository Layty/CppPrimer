// 解释 make_shared 是如何工作的。
// 最简单的一种重载是
// template< class T, class... Args >
// shared_ptr<T> make_shared( Args&&... args );

// 我们在使用的时候, shared_ptr<string> a=make_shared<string>("123");

// 1. 转发扩展包给 class T 的构造函数
// 2. 内部提取地址到shared<T>

#include <memory>
#include <string>
#include <iostream>
using namespace std;

template <class T, class... Args>
shared_ptr<T> my_make_shared(Args &&... args)
{
    shared_ptr<T> ret(new T(std::forward<Args>(args)...));

    return ret;
}

int main(int argc, char const *argv[])
{
    shared_ptr<string> s1 = my_make_shared<string>("123");
    std::cout << *s1 << std::endl;
    while (1)
        ;
    return 0;
}
