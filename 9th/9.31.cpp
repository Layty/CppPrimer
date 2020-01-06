// 大佬使用了  advance(prv, 2) 来操作迭代器

/*第316页中删除偶数值元素并复制奇数值元素的程序不能用于list或forward_list。
修改程序，使之也能用于这些类型
*/
#include <forward_list>
#include <iostream>
#include <list>
#include <vector>
using namespace std;

template <typename T> 
void print(T src)
{
    for (auto ch : src) 
        cout << ch <<",";
    cout<<endl;
}

int main(int argc, const char** argv)
{
    vector<int> v1 = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    list<int> l1(v1.begin(),v1.end());
    forward_list<int> l2(v1.begin(),v1.end());


    // 删除偶数元素,复制每个奇数元素
    auto it1 = v1.begin();
    while (it1 != v1.end()) {
        if (*it1 % 2) {
            it1 = v1.insert(it1, *it1);
            it1+=2;
        }
        else {
            it1=v1.erase(it1);
        }
    }
    print(v1);


    {   // list 使用两个++
        // 删除偶数元素,复制每个奇数元素
        auto it1 = l1.begin();
        while (it1 != l1.end()) {
            if (*it1 % 2) {
                it1 = l1.insert(it1, *it1);
                it1++;
                it1++;

            }
            else {
                it1=l1.erase(it1);
            }
        }
        print(l1);
    }


    {   // forward_list 只有insert_after
        // 删除偶数元素,复制每个奇数元素
        auto curr = l2.begin();
        auto prev=l2.before_begin();
        while (curr != l2.end()) {
            if (*curr % 2) {
                prev = l2.insert_after(prev,*curr); 
                prev++;         // 指向了原来的curr
                //curr=prev;    // 可以注释掉,这里不会发生迭代器失效
                curr++;
            }
            else {
                curr=l2.erase_after(prev);
            }
        }
        print(l2);
    }

    while (1);

    return 0;
}