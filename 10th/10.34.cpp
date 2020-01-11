/*
1. 反向迭代器 逆序输出vector
2. 普通迭代器 逆序输出
*/
#include "include.h"
#include <iterator>
int main(int argc, char const *argv[])
{
    vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    copy(v.crbegin(), v.crend(), ostream_iterator<int>(cout, ","));
    cout << endl;

    //copy(v.crbegin(), v.crend(), ostream_iterator<int>(cout, ","));
    auto beg1 = v.end() - 1;
    for (; beg1 != v.begin(); advance(beg1, -1))
    {
        cout << *beg1 << ",";
    }
    cout << *beg1 << endl;

    
    while (1)
        ;
    return 0;
}
