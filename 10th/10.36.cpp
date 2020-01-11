/*使用find在一个int的list中查找最后一个值为0的元素。*/
/*给定一个包含10个元素的vector，将位置3到7之间的元素按逆序拷贝到一个list中*/

#include "include.h"
int main(int argc, char const *argv[])
{
    list<int> l = {1, 2, 3, 5, 0, 1, 2, 5, 8, 2, 0, 3, 15};

    auto last_zero_it = find(l.crbegin(), l.crend(), 0);
    cout << distance(last_zero_it, l.crend()) << endl;
    for_each(l.cbegin(), last_zero_it.base(), [](const int c) { cout << c << ","; });
    cout << endl;

    //////////end   -1  -2
    vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    list<int> l2(v.rend() - 7, v.rend() - 2);
    for_each(l2.cbegin(), l2.cend(), [](const int c) { cout << c << ","; });

    //// 另一种方式,但是他这种对于vector不友好,一直在头部插入,对于list无所谓
    ////copy(vec.cbegin() + 3, vec.cbegin() + 8, ret_lst.rbegin());

    while (1)
        ;
    return 0;
}
