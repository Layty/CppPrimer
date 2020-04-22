// 16.53 编写你自己版本的 print 函数，并打印一个、两个及五个实参来测试它，要打印的每个实参都应有不同的类型。

#include <iostream>
#include <vector>
using namespace std;

template <typename T>
ostream &print(ostream &o, const T &s)
{
    return o << s << endl;
}

template <typename A, typename... T>
ostream &print(ostream &o, const A &a, const T &... s)
{
    o << a << ",";
    return print(o, s...);
}

int main(int argc, const char **argv)
{
    int i = 1;
    double d = 3.14;
    float f = 99.99;
    string s = "hello";

    print(std::cout, i);
    print(std::cout, i, s);
    print(std::cout, i, d, f, s, "123456");

    //no match for 'operator<<' (operand types are 'std::ostream {aka std::basic_ostream<char>}' and 'const std::vector<int>')
    //print(std::cout, i, d, f, s, vector<int>(1));

    while (1)
        ;

    return 0;
}