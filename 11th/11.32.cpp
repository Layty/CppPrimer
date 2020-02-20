/*
使用上一题定义的multimap编写一个程序，按字典序打印作者列表和他们的作品。
**/

/*编写程序，定义一个作者及其作品的multimap。使用find在multimap中查找一个元素并用erase删除它。确保你的程序在元素不在map中时也能正常运行。*/

#include "../include/include.h"

void printMap(const multimap<string, string> &m)
{
    for (auto ch : m)
        cout << ch.first << ":" << ch.second << endl;
}

int main(int argc, char const *argv[])
{
    multimap<string, string> m;
    m.insert({"a", "1"});
    m.insert({"b", "2"});
    m.insert({"c", "3"});
    m.insert({"d", "4"});
    m.insert({"a", "2"});
    m.insert({"a", "3"});
    m.insert({"a", "4"});
    printMap(m);

    map<string, multiset<string>> m2;
    for (auto ch : m)
    {
        m2[ch.first].insert(ch.second);
    }
    for (auto ch : m2)
    {
        cout << ch.first << ":" << endl;
        for (auto l : ch.second)
            cout << l << "+";
        cout << endl;
    }

    while (1)
        ;
    return 0;
}
