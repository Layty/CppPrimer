/*
使用一个map迭代器编写一个表达式，将一个值赋予一个元素
*/

#include "../include/include.h"
#include <map>

int main(int argc, char const *argv[])
{
    map<int, string> v;
    v[10] = "123";
    auto it = v.begin();
    cout << it->second << endl;

    it->second = "555";
    cout << it->second << endl;

    while (1)
        ;
    return 0;
}
