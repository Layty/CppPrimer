// 16.62 定义你自己版本的 hash<Sales_data>, 并定义一个 Sales_data 对象的 unorder_multise。将多条交易记录保存到容器中，并打印其内容
// p396
// 无序容器需要提供 元素的== 以及哈希函数
// 需要提供hash<类型>的模版,一个 ()运算返回size_t 表示hash值
#include <string>
#include <vector>
#include <iostream>
#include <unordered_set>
using namespace std;

class Sales_data
{
    friend bool operator==(const Sales_data &, const Sales_data &);
    friend std::hash<Sales_data>;

private:
    string isbn;
    unsigned units_sold = 0;
    double revenue = 0.0;

public:
    Sales_data(string isbn, unsigned units_sold, double revenue) : isbn(isbn), units_sold(units_sold), revenue(revenue) {}

    double avg_price() { return revenue / units_sold; }
    void print() { std::cout << "name=" << isbn << " aver_price= " << avg_price() << std::endl; }
    string prints() { return string("name=") + isbn + " aver_price= " + to_string(avg_price()); }
};

bool operator==(const Sales_data &a, const Sales_data &b)
{
    return (a.isbn == b.isbn) && (a.revenue == b.revenue) && (a.units_sold == b.units_sold);
}

namespace std
{
template <>
struct hash<Sales_data>
{
    typedef size_t result_type;
    typedef Sales_data argument_type;
    size_t operator()(const Sales_data &s) const
    {
        return hash<string>()(s.isbn) ^
               hash<unsigned>()(s.units_sold) ^
               hash<double>()(s.revenue);
    }
};
} // namespace std

int main(int argc, const char **argv)
{
    Sales_data A1("A1", 5, 17);
    A1.print();

    std::unordered_multiset<Sales_data> mset;

    mset.emplace(A1);
    mset.emplace("C++ Primer", 5, 9.99);

    for (auto ch : mset)
        std::cout << "hash()=" << std::hex << std::hash<Sales_data>()(ch) << ch.prints() << std::endl;

    while (1)
        ;
    return 0;
}