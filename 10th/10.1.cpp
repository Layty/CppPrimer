/*
头文件algorithm中定义了一个名为count的函数，它类似find，接受一对迭代器和一个值作为参数。count返回给定值在序列中出现的次数。
编写程序，读取int序列存入vector中，打印有多少个元素的值等于给定值
*/
#include "algorithm"
#include "include.h"

int main(int argc, char const *argv[])
{
    vector<int> v = {1, 2, 3, 4, 5, 6, 3, 8, 9, 3, 5, 5};
    auto findme = count(v.begin(), v.end(), 3);
    cout << findme << endl;
    while (1)
        ;
    return 0;
}
