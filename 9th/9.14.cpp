/*
编写程序，将一个list中的char*指针（指向C风格字符串）元素赋值给一个vector中的string
*/

#include <iostream>
#include <list>
#include <string>
#include <vector>
using namespace std;

int main(int argc, const char** argv)
{

    list<const char*> a(10, "hello");
    vector<string> b;
    b.assign(a.begin(), a.end());
    for (auto ch : b) cout << ch << endl;

    while (1)
        ;
}