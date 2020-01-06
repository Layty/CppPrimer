/*
使用下面代码定义的ia，将ia拷贝到一个从vector和一个list中。
使用单迭代器版本的erase从list中删除奇数元素，从vector中删除偶数元素。
*/
#include <iostream>
#include <list>
#include <vector>
using namespace std;

int main(int argc, const char** argv)
{
    int ia[] = {0, 1, 1, 2, 3, 5, 8, 13, 21, 55, 89};

    // 这么做也可以,说明迭代器是+1的计算方式
    // vector<int> va(ia, ia + sizeof(ia) / sizeof(int));
    vector<int> va(begin(ia), end(ia));

    list<int> lb(va.begin(), va.end());

    for (auto it = va.begin(); it != va.end();) {
        if ((*it) % 2)
            it = va.erase(it);
        else
            it++;
    }

    for (auto it = lb.begin(); it != lb.end();) {
        if ((*it) % 2)
            it++;
        else
            it = lb.erase(it);
    }

    for (auto ch : va) cout << ch << ",";
    cout << endl;
    for (auto ch : lb) cout << ch << ",";
    cout << endl;

    while (1)
        ;
    return 0;
}