// what the difference between sizeof..(typename) and sizeof..(parameter)  in variadic  template
#include <iostream>
using namespace std;

template <typename T, typename... Args>
void foo(const T &t, const Args &... rest)
{
    std::cout << "sizeof...(Args)=" << sizeof...(Args) << "  sizeof...(rest)=" << sizeof...(rest) << std::endl;
}

int main(int argc, const char **argv)
{
    int i = 0;
    double d = 3.14;
    string s = "how";

    foo(i, s, 42, d); /// sizeof...(Args)=3  sizeof...(rest)=3
    foo(s, 42, "hi"); /// sizeof...(Args)=2  sizeof...(rest)=2
    foo(d, s);        /// sizeof...(Args)=1  sizeof...(rest)=1
    foo("hi");        /// sizeof...(Args)=0  sizeof...(rest)=0
    foo(i, s, s, d);  /// sizeof...(Args)=3  sizeof...(rest)=3

    while (1)
        ;
    return 0;
}
