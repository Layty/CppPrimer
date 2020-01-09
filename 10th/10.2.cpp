/*
头文件algorithm中定义了一个名为count的函数，它类似find，接受一对迭代器和一个值作为参数。count返回给定值在序列中出现的次数。
编写程序，读取string序列存入list中，打印有多少个元素的值等于给定值
*/

#include "include.h"

int main(int argc, char const *argv[])
{

    list<string> l = {"123", "456", "111", "123", "456", "123"};

    auto has = count(l.begin(), l.end(), "123");
    cout << "123 has " << has << endl;

    while (1)
        ;
    return 0;
}
