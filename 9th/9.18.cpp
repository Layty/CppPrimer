/*
编写程序，从标准输入读取string序列，存入一个deque中。编写一个循环，用迭代器打印deque中的元素
备注: 这里需要使用ctrl+z
*/

#include <deque>
#include <string>
#include <vector>

#include <iostream>
using namespace std;

int main(int argc, const char** argv)
{

    string tmp;
    deque<string> put;
    while (cin >> tmp) {
        put.push_back(tmp);
    }
    cout << "you input :\n";

    for (auto ch = put.begin(); ch != put.end(); ch++) {
        cout << *ch << endl;
    }

    while (1) {
        /* code */
    }

    return 0;
}