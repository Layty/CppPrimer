/*
实现你自己的elimDups。测试你的程序，分别在读取输入后、调用unique后以及调用erase后打印vector的内容
*/

#include "include.h"

void elimDups(vector<string> &s)
{
    print(s);
    sort(s.begin(), s.end());
    print(s);
    auto last = unique(s.begin(), s.end());
    print(s);
    s.erase(last, s.end());
    print(s);
}

int main(int argc, char const *argv[])
{
    vector<string> vs = {"999",
                         "123",
                         "456",
                         "123",
                         "777",
                         "999"};

    elimDups(vs);
    while (1)
        ;
    return 0;
}
