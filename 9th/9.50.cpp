/*
编写程序处理一个vector,其元素都表示整形值。计算vector中所有元素之和。修改程序，使之计算表示浮点值的string之和
*/

#include "include.h"
int sum_int(const vector<string>& s)
{
    int  n=0;
    for(auto ch : s)
    {   
        if(ch.find_first_of("0123456789")!=string::npos)
            if(ch.substr(ch.find_first_of("+-.0123456789")).size())
            {
                n+=stoi(ch);
            }

    }
    return n;
}

double sum_double(const vector<string>& s)
{
    double  n=0;
    for(auto ch : s)
    {   
        if(ch.find_first_of("0123456789")!=string::npos)
            if(ch.substr(ch.find_first_of("+-.0123456789")).size())
            {
                n+=stod(ch);
            }

    }
    return n;
}


int main(int argc, char const *argv[])
{
    vector<string> s={"---","2.1","2.1","-3"};
    cout << "sum="<<sum_int(s)<<endl;
    cout << "sum="<<sum_double(s)<<endl;
    while(1);
    return 0;
}
