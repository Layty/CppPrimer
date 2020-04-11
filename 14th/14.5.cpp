/*
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
    Date(int y, int m, int d, int h, int mi, int s) : year(y), month(m), day(d), hour(h), min(mi), sec(s) {}
    friend std::ostream &operator<<(std::ostream &o, Date &d);
};

std::ostream &operator<<(std::ostream &o, Date &d)
{
    return o << d.year << "-" << d.month << "-" << d.day << " " << d.hour << ":" << d.min << ":" << d.sec;
}

int main(int argc, const char **argv)
{

    Date d(2020, 4, 9, 14, 17, 5);
    std::cout << d << std::endl;
    while (1)
        ;
    return 0;
}
