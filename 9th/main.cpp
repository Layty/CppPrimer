
#include <iostream>
#include <memory>
#include <string>
#include <vector>
using namespace std;

int main()
{

    vector<int> a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
                     0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 7, 8, 9, 0, 1, 2, 3, 4, 5,
                     6, 7, 8, 9, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    vector<int>::iterator it1 = a.begin();

    vector<char> b = {1, 2, 3, 4, 5, 6, 7};
    vector<char>::iterator it2 = b.begin();

    int size_it1 = sizeof(it1);
    int size_it2 = sizeof(it2);

    cout << "sizeof(vector<int>::iterator)=" << size_it1 << endl;  // 8
    cout << "sizeof(vector<char>::iterator)=" << size_it2 << endl; // 8

    // 地址+4
    cout << &*it1 << endl;
    it1++;
    cout << &*it1 << endl;

    // 地址+1,这里不知道为啥不能直接使用cout打印,打印的是char*
    cout << (static_cast<void*>(&*it2)) << endl;
    it2++;
    cout << (static_cast<void*>(&*it2)) << endl;

    cout << "sizeof(vector<int>)=" << sizeof(a) << endl; //存的也是数据的地址
    cout << "sizeof(vector<char>)=" << sizeof(b) << endl;

    while (1)
        ;

    return 0;
}
