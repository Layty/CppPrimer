// 在16.3节中我们定义了两个重载的 debug_rep 版本，一个接受 const char* 参数，另一个接受 char * 参数。将这两个函数重写为特例化版本。
// 16.48 编写你自己版本的 debug_rep 函数。

#include <iostream>
#include <string>
#include <sstream>
using std::string;

string debug_rep(const string &t)
{
    return "String:" + t;
}

template <typename T>
string debug_rep(const T &t)
{
    std::ostringstream ret;
    ret << t;
    return ret.str();
}

template <typename T>
string debug_rep(T *t)
{
    std::ostringstream ret;
    ret << "Point Addr=" << t;
    if (t == nullptr)
        ret << "nullptr";
    else
        ret << debug_rep(*t);
    return ret.str();
}
template <>
string debug_rep(const char *t)
{
    return string("const char*") + debug_rep(string(t));
}
template <>
string debug_rep(char *t)
{
    return "char*" + debug_rep(string(t));
}

// string debug_rep(const char *t)
// {
//     return "const char*" + debug_rep(string(t));
// }

int main(int argc, const char **argv)
{

    std::cout << debug_rep("123456") << std::endl;
    while (1)
        ;

    return 0;
}
