/*
编写程序，使用 stable_sort 和isShorter将传递给你的elimDups版本的vector排序。打印vector的内容，验证你的程序的正确性。
*/

#include "include.h"

bool isShorter(const string &a, const string &b)
{
    return a.size() < b.size();
}

void elimDups(vector<string> &s)
{
    print(s);
    sort(s.begin(), s.end());
    print(s);
    auto last = unique(s.begin(), s.end());
    print(s);
    s.erase(last, s.end());
    print(s);

    stable_sort(s.begin(), s.end(), isShorter);
    print(s);
}

int main(int argc, char const *argv[])
{
    vector<string> vs = {"9990000",
                         "123000000000",
                         "456",
                         "123000000000",
                         "777",
                         "9990000"};

    elimDups(vs);
    while (1)
        ;
    return 0;
}
