/*
求一个大于等于给定长度的单词有多少,并将其打印出来
void biggiest(vector<string>v,vector<string>::size_type sz)
*/
#include "include.h"

void biggiest(vector<string> v, vector<string>::size_type sz)
{
    // 按照字典排序,删除重复单词
    sort(v.begin(), v.end());
    auto last = unique(v.begin(), v.end());
    v.erase(last, v.end());

    // 按照长度排序,这里需要传递一个长度 使用lamada
    stable_sort(v.begin(), v.end(), [](const string &a, const string &b) { return a.size() < b.size(); });

    //找到第一个长度>sz的迭代器
    auto fst = find_if(v.begin(), v.end(), [sz](const string &a) { return a.size() >= sz; });

    // 打印vec
    for_each(fst, v.end(), [](const string &a) { cout << a << endl; });
}

int main(int argc, char const *argv[])
{
    vector<string> v = {"0", "123", "1234", "hello", "world", "99999999999", "world"};
    biggiest(v, 4);

    while (1)
        ;
    return 0;
}
