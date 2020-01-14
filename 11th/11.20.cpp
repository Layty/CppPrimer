/*
重写11.1节练习的单词计数程序，使用inserter代替下标操作。你认为哪个程序更容易编写和阅读？
*/

/*
11.3 编写你自己的单词计数程序
11.4 忽略大小写和标点。例如，“example.”、"example,"和"Example"应该递增相同的计数器
*/

#include "../include/include.h"
#include <ctype.h>

int main(int argc, char const *argv[])
{
    map<string, size_t> dic;
    string ch;

    while (cin >> ch)
    {
        for (auto &c : ch)
            c = tolower(c);

        auto lst = find_if(ch.crbegin(), ch.crend(), [](const char &ch) { return !ispunct(ch); });
        ch.erase(lst.base(), ch.cend());

        //dic[ch]++;
        // auto it = dic.insert({ch, 1});
        // if (false == it.second)
        // {
        //     (it.first->second)++;
        // }

        ++dic.insert({ch, 0}).first->second;
    }

    for (auto &ch : dic)
    {
        cout << ch.first << "  has " << ch.second << endl;
    }
    while (1)
        ;

    return 0;
}