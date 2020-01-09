/*
一个vector中保存1到9共9个值，将其拷贝到三个其他容器中。分别使用inserter、back_inserter 和front_inserter将元素添加到三个容器中。
对每种 inserter，估计输出序列是怎样的，运行程序验证你的估计是否正确
*/

#include "include.h"

int main(int argc, char const *argv[])
{
    vector<int> v;
    list<int> v1;
    list<int> v2;
    list<int> v3;

    for (int i = 0; i < 9; i++)
        v.push_back(i);

    copy(v.begin(), v.end(), inserter(v1, v1.begin())); // 0,1,2,3,4,5,6,7,8,
    copy(v.begin(), v.end(), back_inserter(v2));        // 0,1,2,3,4,5,6,7,8,
    copy(v.begin(), v.end(), front_inserter(v3));       // 8,7,6,5,4,3,2,1,0,

    for_each(v1.begin(), v1.end(), [](const int ch) { cout << ch << ","; });
    cout << endl;
    for_each(v2.begin(), v2.end(), [](const int ch) { cout << ch << ","; });
    cout << endl;
    for_each(v3.begin(), v3.end(), [](const int ch) { cout << ch << ","; });
    cout << endl;

    while (1)
        ;
    return 0;
}
