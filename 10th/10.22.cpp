/*
重写统计长度小于等于6的单词数量的程序,使用函数代替lambda.
*/
#include "include.h"
#include <functional>
using namespace std::placeholders;
bool cnt(const string &a, string::size_type sz)
{
    return a.size() <= sz;
}

int main(int argc, char const *argv[])
{

    vector<string> v = {"123", "1233", "ssss", "123456789", "123564789"};

    //auto f = bind(cnt, _1, 6);
    //auto cnt = count_if(v.begin(), v.end(), f);

    auto cnt = count_if(v.begin(), v.end(), bind(cnt, _1, 6));
    cout << cnt << endl;
    while (1)
        ;
    return 0;
    while (1)
        ;
    return 0;
}
