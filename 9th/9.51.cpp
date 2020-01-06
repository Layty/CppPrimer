/*
设计一个类，它有三个unsigned成员，分别表示年、月和日。为其编写构造函数，接受一个表示日期的string参数。你的构造函数应该能处理不同数据格式，如January 1，1900、1/1/1990、Jan 1 1900等。
*/
#include "include.h"
#include <array>


class mydate
{
private:
    /* data */
    unsigned int year=1990;
    unsigned int month=1;
    unsigned int day=1;
public:
    mydate(const string& s);
    ~mydate();
};

mydate::mydate(const string& s1="")
{
    string s(s1);
    if(s.empty()) return;

    string::size_type pos;
    string::size_type year_pos,month_pos;
    string::size_type pos_day,pos_month,pos_year;
    if((pos=s.find("/"))!= string::npos) // 1/1/1990
    {
        // day
        s=s.substr(s.find_first_of("0123456789"));
        day=stoul(s,&pos_day);
        // month
        s=s.substr(s.find_first_of("0123456789",pos_day));
        month=stoul(s,&pos_month);
        // year
        s=s.substr(s.find_first_of("0123456789",pos_month));
        year=stoul(s);

    } 
    else    //Jan 1 1900
    {
        std::array<std::string, 12> month_names{"Jan", "Feb", "Mar", "Apr", "May", "Jun","Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
        for(int i=0;i<12;i++)
        {
            if(s.find(month_names[i])!=string::npos)
            {
                 month=i+1;
                 break;
            }   
        }
        // day
        s=s.substr(s.find_first_of("0123456789"));
        day=stoul(s,&pos_day);
        // year
        s=s.substr(s.find_first_of("0123456789",pos_day));
        year=stoul(s);


        
    }
    
    cout<< "year="<<year<<" month="<<month<<" day="<<day<<endl;
}

mydate::~mydate()
{
}




int main(int argc, char const *argv[])
{
    mydate("3/4/2021");
    mydate("Dec 2 2022");
    mydate("January 1，2023");
    
    while(1);
    return 0;
}
