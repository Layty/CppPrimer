/*
编写一个程序，在一个vector而不是一个set中保存不重复的单词。使用set的优点是什么
*/

#include "../include/include.h"
int main(int argc, char const *argv[])
{
    vector<string> v;
    string ch;
    while (cin >> ch)
    {
        v.push_back(ch);
    }

    sort(v.begin(), v.end());
    auto lst = unique(v.begin(), v.end());
    v.erase(lst, v.end());
    print(v);

    while (1)
        ;
    return 0;
}
