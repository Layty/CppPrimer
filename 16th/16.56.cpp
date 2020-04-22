// 16.56 编写并测试可变参数版本的 errorMsg。
#include <initializer_list>
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

/*********************************************************************/
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

string debug_rep(const string &t)
{
    return "String:" + t;
}

string debug_rep(char *t)
{
    return "char*" + debug_rep(string(t));
}

string debug_rep(const char *t)
{
    return "const char*" + debug_rep(string(t));
}

/*********************************************************************/

void err_msg_old(initializer_list<string> il)
{
    for (auto ch : il)
        std::cout << ch << ",";
    std::cout << std::endl;
}

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

template <typename... T>
ostream &err_msg(ostream &o = std::cout, const T &... s)
{
    // 这里会展开  debug_rep(int) debug_rep(char)
    return print(o, debug_rep(s)...);
}

int main(int argc, char const *argv[])
{
    err_msg_old({"1", "2", "3"});
    err_msg(std::cout, "1", 1, 3.14);
    while (1)
        ;
    return 0;
}
