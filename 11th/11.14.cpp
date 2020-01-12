/*
扩展你在11.7节练习中编写的孩子姓到名的map，添加一个pair的vector，保存孩子的名字和生日
jack 1 11-12
jack 2 11-13
cc 1 1-5
cc 5 5-8
jack 21 15-55
^Z
family: cc
child: 1,1-5
5,5-8

family: jack
child: 1,11-12
2,11-13
21,15-55
*/

/**
 * 11.7 定义一个map，关键字是家庭的姓，值是一个vector，保存家中孩子们的名。编写代码，实现添加新的家庭以及向已有家庭中添加新的孩子
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
    map<string, vector<pair<string, string>>> people; // modify

    string family, child, day;

    while (cin >> family >> child >> day) // modify
    {
        people[family].push_back(make_pair(child, day)); // modify
    }

    for (auto ch : people)
    {
        cout << "family: " << ch.first << endl;
        cout << "child: ";
        for (auto c : ch.second)
        {
            cout << c.first << "," << c.second << endl; // modify
            ;
        }
        cout << endl;
    }

    while (1)
        ;
    return 0;
}
