//重新10.12的程序，在对sort的调用中使用lambda来代替函数compareIsbn

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
    vector<Sales_data> v2(v);
    sort(v.begin(), v.end(), compareIsbn);

    for (auto ch : v)
    {
        cout << ch.isbn() << endl;
    }

    sort(v2.begin(), v2.end(), [](const Sales_data &a, const Sales_data &b) { return a.isbn() < b.isbn(); });
    for (auto ch : v2)
    {
        cout << ch.isbn() << endl;
    }

    while (1)
        ;
    return 0;
}
