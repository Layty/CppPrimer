/*
使用list代替vector重新实现10.2.3节中的去除重复单词的程序
*/

#include "include.h"

int main(int argc, char const *argv[])
{
    list<string> l = {"1",
                      "my",
                      "2",
                      "3",
                      "2",
                      "heel",
                      "my"};
    l.sort();
    l.unique();
    for_each(l.begin(), l.end(), [](const string &c) { cout << c << endl; });
    while (1)
        ;
    return 0;
}
