/*
    14.45 编写类型转换运算符转换 Sales_data 到 string 和double
*/

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
    friend Sales_data operator+(Sales_data &a, Sales_data &b);
    friend Sales_data operator-(Sales_data &a, Sales_data &b);

public:
    Sales_data(const string &bookNo, unsigned units, double revenue) : bookNo(bookNo), units_sold(units), revenue(revenue)
    {
    }
    Sales_data() : bookNo("default id"), units_sold(0), revenue(0) {}
    Sales_data &operator+=(const Sales_data &b)
    {
        units_sold += b.units_sold;
        revenue += b.revenue;
    }
    Sales_data &operator-=(const Sales_data &b)
    {
        units_sold -= b.units_sold;
        revenue -= b.revenue;
    }

    operator const string() { return bookNo; }
    operator const double() { return GetAvg(); }

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
Sales_data operator+(Sales_data &a, Sales_data &b)
{
    return Sales_data(a.bookNo, a.units_sold + b.units_sold, a.revenue + b.revenue);
}
Sales_data operator-(Sales_data &a, Sales_data &b)
{
    return Sales_data(a.bookNo, a.units_sold - b.units_sold, a.revenue - b.revenue);
}

int main(int argc, char const *argv[])
{
    Sales_data book1("ID1001", 10, 38);
    cout << book1 << endl;

    cout << static_cast<string>(book1) << endl;
    cout << static_cast<double>(book1) << endl;
    while (1)
        ;
    return 0;
}
