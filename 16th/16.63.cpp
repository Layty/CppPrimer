
// 16.64 为上一题的模版编写特例化版本来处理vector<const char*>。编写程序使用这个特例化版本。
// 16.63 定义一个函数模版，统计一个给定值在一个vecor中出现的次数。
// 测试你的函数，分别传递给它一个double的vector，一个int的vector以及一个string的vector。

#include <algorithm>
#include <string>
#include <iostream>
#include <vector>
using namespace std;

template <typename T>
int GetCount(T elem, const vector<T> &v)
{
    std::cout << __LINE__ << "   :GetCount(T elem, const vector<T> &v)" << std::endl;
    int i = 0;
    for (auto ch : v)
    {
        if (ch == elem)
            i++;
    }
    return i;
}

template <>
int GetCount(const char *elem, const vector<const char *> &v)
{
    std::cout << __LINE__ << "   :GetCount(const char *elem, const vector<const char *> &v)" << std::endl;
    int i = 0;
    for (auto ch : v)
    {
        if (string(ch) == string(elem))
            i++;
    }
    return i;
}

int GetCount(const char *elem, const vector<string> &v)
{
    std::cout << __LINE__ << "    :GetCount(const char *elem, const vector<string> &v)" << std::endl;
    return GetCount(string(elem), v);
}

int GetCount(const int elem, const vector<double> &v)
{
    return GetCount((double)elem, v);
}

int main(int argc, char const *argv[])
{
    vector<string> s({"123", "456", "789", "123", "222"});
    std::cout << GetCount("123", s) << std::endl;
    std::cout << GetCount(string("123"), s) << std::endl;

    vector<int> i = {1, 2, 3, 4, 5, 6, 1, 2};
    std::cout << GetCount(1, i) << std::endl;

    // vector<double> d = {1.0, 2.5, 3, 4, 5, 6, 1, 2};
    // std::cout << GetCount(1, d) << std::endl;

    vector<const char *> s3({"123", "456", "789", "123", "222"});
    std::cout << GetCount("123", s3) << std::endl;

    while (1)
        ;
    return 0;
}
