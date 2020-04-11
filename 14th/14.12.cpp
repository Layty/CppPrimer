/*
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
    Date() = default;
    Date(int y, int m, int d, int h, int mi, int s) : year(y), month(m), day(d), hour(h), min(mi), sec(s) {}
    friend std::ostream &operator<<(std::ostream &o, Date &d);
    friend std::istream &operator>>(std::istream &i, Date &d);
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

int main(int argc, const char **argv)
{

    Date d(2020, 4, 9, 14, 17, 5);
    std::cout << d << std::endl;

    while (1)
    {
        std::cout << "pls input date" << std::endl;
        std::cin >> d;
        std::cout << d << std::endl;
    }

    while (1)
        ;
    return 0;
}
