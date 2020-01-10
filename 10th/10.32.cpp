/*
10.32 重写1.6节的书店程序，使用一个vector保存交易记录，使用不同算法完成处理。使用sort和10.3.1节中的compareIsbn函数来排序交易记录，然后使用find和accumulate求和。
*/

#include "include.h"
#include "../include/Sales_item.h"
#include <numeric>
#include <iterator>

void TestNew()
{
    cout << "Usage input: name_id[string] ,count[unsigned] , value[doubel]" << endl;
    istream_iterator<Sales_item> in(cin), eof;
    vector<Sales_item> v(in, eof);
    sort(v.begin(), v.end(), compareIsbn);
    for (auto beg = v.cbegin(), end = beg; beg != v.cend(); beg = end)
    {
        end = find_if(beg, v.cend(), [beg](const Sales_item &nextv) { return nextv.isbn() != beg->isbn(); });
        cout << accumulate(beg, end, Sales_item(beg->isbn())) << endl;
    }

    // std::istream_iterator<Sales_item> in_iter(std::cin), in_eof;
    // std::vector<Sales_item> vec;

    // while (in_iter != in_eof)
    //     vec.push_back(*in_iter++);
    // sort(vec.begin(), vec.end(), compareIsbn);
    // for (auto beg = vec.cbegin(), end = beg; beg != vec.cend(); beg = end)
    // {
    //     end = find_if(beg, vec.cend(), [beg](const Sales_item &item) { return item.isbn() != beg->isbn(); });
    //     std::cout << std::accumulate(beg, end, Sales_item(beg->isbn())) << std::endl;
    // }
}

int TestOld(void)
{
    cout << "Usage input: name_id[string] ,count[unsigned] , value[doubel]" << endl;
    Sales_item last;

    if (cin >> last)
    {
        Sales_item now;
        while (cin >> now)
        {
            if (now.isbn() == last.isbn())
            {
                last += now;
            }
            else
            {
                cout << last << endl;
                last = now;
            }
        }
        cout << now << endl;
    }
    else
    {
        cout << "input err " << endl;
        return -1;
    }
    return 0;
}
int main(int argc, char const *argv[])
{
    //TestOld();
    TestNew();
    while (1)
        ;
    return 0;
}
