// 16.19 接受容器的引用,打印容器的元素.使用 size_type 和size 控制打印
// 16.20 使用迭代器
#include <iostream>
#include <vector>
#include <list>
#include <string>
using namespace std;

template <typename T>
printv(const T &v)
{
    for (typename T::size_type i = 0; i < v.size(); i++)
        cout << v.at(i) << "<>";
    cout << endl;
}

template <typename T>
printv2(const T &v)
{
    for (auto c = v.begin(); c != v.end(); c++)
        cout << *c << "<>";
    cout << endl;
}

int main(int argc, char const *argv[])
{
    vector<int> v1({1, 2, 3, 4, 5, 6, 7});
    printv(v1);

    //因为printv使用的是 size 不是迭代器,所以不能用list
    list<string> v2({"123", "456"});
    printv2(v2);

    while (1)
        ;
    return 0;
}
