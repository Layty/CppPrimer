/*
下面程序是否有错误？如果有，请改正。
reserve 只是确保当前size<capacity,扩充容量但是不会改变size
*/
#include "include.h"

int main(int argc, char const *argv[])
{
    vector<int> vec;
    list<int> lst;
    int i;
    while (cin >> i)
        lst.push_back(i);

    //-------------------
    //vec.reserve(lst.size()); // 虽然不会报错误,但是不会有打印的

    //ok1
    //vec.resize(lst.size());
    //copy(lst.cbegin(), lst.cend(), vec.begin());

    //ok2
    copy(lst.cbegin(), lst.cend(), back_inserter(vec));

    print(vec);

    while (1)
        ;

    return 0;
}
