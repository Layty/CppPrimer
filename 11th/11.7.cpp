/**
 * 定义一个map，关键字是家庭的姓，值是一个vector，保存家中孩子们的名。编写代码，实现添加新的家庭以及向已有家庭中添加新的孩子
 * 
 * family child input
    1 2
    2 21
    1 1
    3 123
    8 12345678
    1 5
    2 22
    ^Z
    family: 1
    chile: 2,1,5,
    family: 2
    chile: 21,22,
    family: 3
    chile: 123,
    family: 8
    chile: 12345678,
 * 
 * 
 * */

#include "../include/include.h"
#include <map>
int main(int argc, char const *argv[])
{
    map<string, vector<string>> people;

    string family, child;

    while (cin >> family >> child)
    {
        people[family].push_back(child);
    }

    for (auto ch : people)
    {
        cout << "family: " << ch.first << endl;
        cout << "chile: ";
        for (auto c : ch.second)
        {
            cout << c << ",";
        }
        cout << endl;
    }

    while (1)
        ;
    return 0;
}
