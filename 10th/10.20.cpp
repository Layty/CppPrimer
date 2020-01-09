/*
标准库定义了一个名为count_if的算法。类似find_if，此函数接受一对迭代器，表示一个输入范围，还接受一个谓词，会对输入范围中每个元素执行。
count_if返回一个计数值，表示谓词有多少次为真。使用count_if重写我们程序中统计有多少单词长度超过6的部分。
*/
#include "include.h"

int main(int argc, char const *argv[])
{
    vector<string> v = {"123", "1233", "ssss", "123456789", "123564789"};

    auto cnt = count_if(v.begin(), v.end(), [](const string &a) { return a.size() > 6; });
    cout << cnt << endl;
    while (1)
        ;
    return 0;
}
