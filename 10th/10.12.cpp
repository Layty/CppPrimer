//编写名为compareIsbn的函数，比较两个Sales_data对象的isbn()成员。使用这个函数排序一个保存Sales_data对象的vector。

#include "Sales_data.h"
#include "include.h"

bool compareIsbn(const Sales_data &a, const Sales_data &b)
{
    return a.isbn() < b.isbn();
}

int main(int argc, char const *argv[])
{
    Sales_data a("999");
    Sales_data b("456");
    Sales_data c("222");

    vector<Sales_data> v = {a, b, c};
    sort(v.begin(), v.end(), compareIsbn);
    for (auto ch : v)
    {
        cout << ch.isbn() << endl;
    }

    while (1)
        ;
    return 0;
}
