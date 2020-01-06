/*
假定iv是一个int的vector，下面的程序存在什么错误？你将如何修改？

vector<int>::iterator iter = iv.begin(), mid = iv.begin() + iv.size()/2;

while(iter != mid) {
    if (*iter == some_val) {
        iv.insert(iter, 2 * some_val);
    }
}

1. iter 是iv 的迭代器,插入后长度变了,mid也就失效了  同时当vector扩大时,地址全部失效了
2. 死循环,iter没有++

insertDoubleValue2 是我写的,,这里取巧了,因为end是一直变的,我们根据end-cursor就好了
*/

#include <iostream>
#include <vector>
using std::vector;

void insertDoubleValue(vector<int>& iv, int some_val)
{
    auto cursor = iv.size() / 2;
    auto iter = iv.begin(), mid = iv.begin() + cursor;
    while (iter != mid) {
        if (*iter == some_val) {
            iter = iv.insert(iter, 2 * some_val);
            ++iter;
            ++cursor;
            mid = iv.begin() + cursor;
        }
        ++iter;
    }
}

void insertDoubleValue2(vector<int>& iv, int some_val)
{
    auto cursor = iv.size() / 2;
    auto iter = iv.begin();
    while (iter != iv.end() - cursor) {
        if (*iter == some_val) {
            iter = iv.insert(iter, 2 * some_val);
            ++iter;
        }
        ++iter;
    }
}

void print(const vector<int>& iv)
{
    for (auto i : iv) std::cout << i << " ";
    std::cout << std::endl;
}

int main()
{
    vector<int> iv = {1, 1, 1, 1, 1, 7, 1, 9, 8};
    insertDoubleValue(iv, 1);
    print(iv);

    iv = {1, 1, 1, 1, 1, 7, 1, 9, 8};
    insertDoubleValue2(iv, 1);
    print(iv);
    while (1)
        ;
}
