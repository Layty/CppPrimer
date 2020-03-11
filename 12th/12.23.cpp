/*
编写一个程序，连接两个字符串字面值常量，将结果保存在一个动态分配的char数组中。重写这个程序，连接两个标准库string对象
*/
#include <string>
#include <string.h>
#include <iostream>

using std::cout;
using std::endl;
using std::string;

int main(int argc, char const *argv[])
{

    const char *c1 = "hello";
    const char *c2 = " world";
    char *c3 = new char[strlen(c1) + strlen(c2) + 1];
    memcpy(c3, c1, strlen(c1));
    memcpy(c3 + strlen(c1), c2, strlen(c2));
    c3[strlen(c1) + strlen(c2)] = 0;

    string s1(c1), s2(c2);
    string s3 = s1 + s2;

    char *s4 = new char[s3.length()];
    strcpy(s4, s3.c_str());

    cout << string(c3) << endl;
    cout << s3 << endl;
    cout << s4 << endl;

    while (1)
        ;
    return 0;
}
