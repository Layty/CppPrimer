/*
除了unique之外，标准库还定义了名为unique_copy的函数，
它接受第三个迭代器，表示拷贝不重复元素的目的位置。
编写一个程序，使用unique_copy将一个vector中不重复的元素拷贝到一个初始为空的list中
*/

#include "include.h"

int main(int argc, char const *argv[])
{

    vector<int> v = {1, 2, 3, 4, 5, 2, 3, 1, 4, 1, 2, 3, 4, 5, 9};
    list<int> l;

    sort(v.begin(), v.end());

    auto last = unique_copy(v.begin(), v.end(), back_inserter(l));

    for_each(l.begin(), l.end(), [](const int &i) { cout << i << " "; });
    cout << endl;

    while (1)
        ;
    return 0;
}
