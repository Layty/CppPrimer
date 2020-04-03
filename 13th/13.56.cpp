/*
    13.56 Foo 右值引用调用的问题
    13.57
    13.58
*/
#include <iostream>
#include <algorithm>
#include <vector>
using std::vector;
class Foo
{
private:
    vector<int> data;

public:
    ~Foo(){};

    push_back(int s) { data.push_back(s); }
    std::ostream &print(std::ostream &o)
    {
        for (auto c : data)
            o << c << ",";
        return o << std::endl;
    }
    Foo sorted() &&;      //用于可以改变的右值
    Foo sorted() const &; // 用于任何类型的Foo
};

Foo Foo::sorted() &&
{
    std::cout << "use &&" << std::endl;
    std::sort(data.begin(), data.end());
    return *this;
}

// 常规版本
// Foo Foo::sorted() const &
// {
//     std::cout << "use const &" << std::endl;
//     Foo ret(*this);
//     std::sort(ret.data.begin(), ret.data.end());
//     return ret;
// }

// // 无限递归
// Foo Foo::sorted() const &
// {
//     std::cout << "use const &" << std::endl;
//     Foo ret(*this);
//     //std::sort(ret.data.begin(), ret.data.end());
//     return ret.sorted();
// }

//  调用&& 一次 后正常输出
Foo Foo::sorted() const &
{
    std::cout << "use const &" << std::endl;
    //std::sort(ret.data.begin(), ret.data.end());
    return Foo(*this).sorted();
}

int main(int argc, const char **argv)
{
    Foo f1;
    f1.push_back(3);
    f1.push_back(1);
    f1.push_back(2);
    Foo f2 = f1.sorted();
    f2.print(std::cout);

    Foo f3 = f2;
    std::move(f3).sorted();
    f3.print(std::cout);

    while (1)
        ;
    return 0;
}