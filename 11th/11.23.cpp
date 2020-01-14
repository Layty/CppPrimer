/*
11.7练习中的map以孩子的姓为关键字，保存他们的名的vector，用multimap重写此map。
*/

/**
 * 定义一个map，关键字是家庭的姓，值是一个vector，保存家中孩子们的名。编写代码，实现添加新的家庭以及向已有家庭中添加新的孩子
 * 
*/

#include "../include/include.h"
#include <map>
int main(int argc, char const *argv[])
{
    //map<string, vector<string>> people;
    multimap<string, string> people;

    string family, child;

    while (cin >> family >> child)
    {
        people.insert({family, child});
    }

    for (auto ch : people)
    {
        cout << "family: " << ch.first << endl;
        cout << "chile: " << ch.second << endl;
    }

    while (1)
        ;
    return 0;
}
