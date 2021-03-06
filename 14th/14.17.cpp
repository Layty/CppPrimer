/*
14.17 重载== 和 !=
14.12 你在7.5.1节的练习中曾经选择并编写了一个类，为它定义一个输入运算符并确保该运算符可以处理输入错误。
14.5 在7.5.1节的练习7.40中，编写了下列类中的某一个框架，请问在这个类中应该定义重载的运算符吗？如果是，请写出来。
     (a)Book    (b)Date    (c)Employee    (d)Vehicle    (e)Object    (f)Tree
*/

#include <iostream>
#include <iomanip>
class Date
{
private:
    int year = 2000;
    int month = 1;
    int day = 1;
    int hour = 0;
    int min = 0;
    int sec = 0;

public:
    friend std::ostream &operator<<(std::ostream &o, Date &d);
    friend std::istream &operator>>(std::istream &i, Date &d);
    friend bool operator!=(const Date &t, const Date &d);
    friend bool operator==(const Date &t, const Date &d);
    Date() = default;
    Date(int y, int m, int d, int h, int mi, int s) : year(y), month(m), day(d), hour(h), min(mi), sec(s) {}
};

std::ostream &operator<<(std::ostream &o, Date &d)
{
    return o << d.year << "-" << d.month << "-" << d.day << " " << d.hour << ":" << d.min << ":" << d.sec;
}

std::istream &operator>>(std::istream &o, Date &ret)
{
    Date d;
    if (o >> d.year >> d.month >> d.day >> d.hour >> d.min >> d.sec)
    {
        ret = d;
    }
    else
    {
        ret = Date();
        o.clear();
        o.sync();
    }
}

bool operator==(const Date &t, const Date &d)
{
    return t.year == d.year && t.month == d.month && t.day == d.day && t.hour == d.hour && t.min == d.min && t.sec == d.sec;
}
bool operator!=(const Date &t, const Date &d)
{
    return !(t == d);
}
int main(int argc, const char **argv)
{

    Date a(2020, 4, 9, 14, 17, 5);
    std::cout << a << std::endl;

    Date b(2020, 1, 9, 14, 17, 5);
    std::cout << b << std::endl;

    std::cout << std::boolalpha << (a == b) << std::endl;
    std::cout << std::boolalpha << (a != b) << std::endl;

    // while (1)
    // {
    //     std::cout << "pls input date" << std::endl;
    //     std::cin >> d;
    //     std::cout << d << std::endl;
    // }

    while (1)
        ;
    return 0;
}
