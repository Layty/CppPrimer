/*
从一个list拷贝元素到两个deque中。值为偶数的所有元素都拷贝到一个deque中，而奇数值元素都拷贝到另一个deque中
*/
#include <deque>
#include <iostream>
#include <list>
#include <string>
#include <vector>
using std::cin;
using std::cout;
using std::deque;
using std::endl;
using std::list;
using std::string;
using std::vector;
// 大佬的代码
// int main()
// {
//     list<int> l{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
//     deque<int> odd, even;
//     for (auto i : l) (i & 0x1 ? odd : even).push_back(i);

//     for (auto i : odd) cout << i << " ";
//     cout << endl;
//     for (auto i : even) cout << i << " ";
//     cout << endl;

//     return 0;
// }

int main()
{
    list<int> src;
    deque<int> dst1;
    deque<int> dst2;

    int num;
    while (cin >> num) src.push_back(num);
    for (int num : src) {
        if (num & 0x01)
            dst1.push_back(num);
        else
            dst2.push_back(num);
    }

    cout << "one" << endl;
    for (int num : dst1) {
        cout << num << " ";
    }
    cout << endl;
    cout << "two" << endl;
    for (int num : dst2) cout << num << " ";

    cout << endl;
    while (1)
        ;
    return 0;
}