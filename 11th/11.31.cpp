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
    m.insert({"a", "4"});
    printMap(m);

    cout << "erace a,4" << endl;
    auto cnt = m.count("a");
    auto it = m.find("a");
    while (cnt)
    {
        if (it->second == "4")
        {
            m.erase(it);
            break; //这里要break,但是这里只会删除一个
        }

        cnt--;
        it++;
    }

    printMap(m);

    // cout << "erace a" << endl;
    // if (m.find("a") != m.end())
    //     m.erase("a");

    // cout << "erace cc" << endl;
    // if (m.find("cc") != m.end())
    //     m.erase("cc");

    while (1)
        ;
    return 0;
}
