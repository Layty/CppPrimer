/*
14.22：定义赋值运算符的一个新版本，使得我们能把一个表示ISBN的string赋给一个Sales_data对象
*/

// 14.20 定义加法 和 复合赋值 +=
// 14.21 + 执行实际加法,+=调用+  , 和+= 执行加法,+调用+=  比较两种做法
// 为Sales_data 重载输入,输出,加法和复合赋值
#include <iostream>
#include <string>

//using namespace std;
using std::cin;
using std::cout;
using std::endl;
using std::istream;
using std::ostream;
using std::string;

class Sales_data
{
    friend ostream &operator<<(ostream &o, const Sales_data &d);
    friend istream &operator>>(istream &o, Sales_data &d);
    friend Sales_data operator+(const Sales_data &a, const Sales_data &b);
    friend Sales_data operator-(Sales_data &a, Sales_data &b);

public:
    Sales_data(const string &bookNo, unsigned units, double revenue) : bookNo(bookNo), units_sold(units), revenue(revenue)
    {
    }
    Sales_data() : bookNo("default id"), units_sold(0), revenue(0) {}
    // Sales_data &operator+=(const Sales_data &b)
    // {
    //     units_sold += b.units_sold;
    //     revenue += b.revenue;
    // }
    Sales_data &operator+=(const Sales_data &b);
    // {
    //     units_sold += b.units_sold;
    //     revenue += b.revenue;
    // }
    Sales_data &operator-=(const Sales_data &b)
    {
        units_sold -= b.units_sold;
        revenue -= b.revenue;
    }

    Sales_data &operator=(const std::string &s)
    {
        bookNo = s;
        return *this;
    }

private:
    std::string bookNo;      // name
    unsigned units_sold = 0; //售卖的数量
    double revenue = 0.0;    //售卖的总价
    double GetAvg() const
    {
        return units_sold ? revenue / units_sold : 0;
    }
};

ostream &operator<<(ostream &o, const Sales_data &d)
{
    o << d.bookNo << ": " << d.units_sold << "," << d.revenue << "," << d.GetAvg() << endl;
}

istream &operator>>(istream &o, Sales_data &d)
{
    cout << "pls input bookNo ,units_sold, revenue" << endl;
    o >> d.bookNo >> d.units_sold >> d.revenue;
    if (!o)
        d = Sales_data();
}

// + 调用 +=
// Sales_data operator+(Sales_data &a, Sales_data &b)
// {
//     //return Sales_data(a.bookNo, a.units_sold + b.units_sold, a.revenue + b.revenue);
//     Sales_data t = a;
//     t += b;
//     return t;
// }
// Sales_data &Sales_data::operator+=(const Sales_data &b)
// {
//     units_sold += b.units_sold;
//     revenue += b.revenue;
//     return *this;
// }

// += 调用+
Sales_data operator+(const Sales_data &a, const Sales_data &b)
{
    Sales_data t = a;
    t.units_sold += b.units_sold;
    t.revenue += b.revenue;
    return t;
}
Sales_data &Sales_data::operator+=(const Sales_data &b)
{
    *this = *this + b;
    return *this;
}

Sales_data
operator-(Sales_data &a, Sales_data &b)
{
    return Sales_data(a.bookNo, a.units_sold - b.units_sold, a.revenue - b.revenue);
}

int main(int argc, char const *argv[])
{
    Sales_data book1("ID1001", 10, 38);
    book1 = "IDChange";
    cout << book1 << endl;

    Sales_data book2("ID1002", 10, 40);
    cout << book2 << endl;

    Sales_data book3 = book1 + book2;
    cout << book3 << endl;

    book3 += book2;
    cout << book3 << endl;

    cin >> book1;
    cout << book1 << endl;

    while (1)
        ;
    return 0;
}
