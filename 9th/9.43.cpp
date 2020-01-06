/*
编写一个函数，接受三个string参数s，oldVal和newVal.使用迭代器及insert和erase函数将s中所有oldVal替换为newVal。测试你的程序，用它替换通用的简写形式，如，将“tho”替换为“though”，将“thru”替换为“through”。

replaceString   迭代器
replaceString0  下标+replace
*/

#include "include.h"



// 使用了下标,和replace
void replaceString0(string& s,string& sold, string& snew)
{
    size_t sold_size=sold.size();
    for(size_t i=0;i+sold_size<s.size();i++)
    {
        if(s.substr(i,sold_size)==sold)
        {
            s=s.replace(i,sold_size,snew);      // replace 可能导致s失效
            i+=snew.size();
        }
    }
}


// 使用了下标,不符合题目
void replaceString1(string& s,string& sold, string& snew)
{
    size_t sold_size=sold.size();
    for(size_t i=0;i+sold_size<s.size();i++)
    {
        if(s.substr(i,sold_size)==sold)
        {
            s.erase(i,sold_size);
            s.insert(i,snew);
            i+=snew.size();
        }
    }
}
// 使用迭代器 转换了下标
void replaceString2(string& s,string& sold, string& snew)
{
    size_t sold_size=sold.size();
    for(auto beg=s.begin(); distance(beg,s.end()) >=distance(sold.begin(),sold.end());beg++)
    {
        if(s.substr(beg-s.begin(),sold_size)==sold)
        {
            s.erase(beg-s.begin(),sold_size);
            s.insert(beg-s.begin(),snew);
            advance(beg,snew.size());
        }
    }
}


// 完全使用迭代器
void replaceString(string& s,string& sold, string& snew)
{
    size_t sold_size=sold.size();
    for(auto beg=s.begin(); distance(beg,s.end()) >=distance(sold.begin(),sold.end());beg++)
    {
        // if(s.substr(beg-s.begin(),sold_size)==sold)
        if(string(beg,beg+sold.size())==sold) 
        {
            beg=s.erase(beg,beg+sold_size);
            beg=s.insert(beg,snew.begin(),snew.end());
            advance(beg,snew.size());
        }
    }
}

int main(int argc, char const *argv[])
{
    {
        string s="123 456 789 ";
        string sold="456";
        string snew="AAAA";
        replaceString(s,sold,snew);
        cout << s <<endl;
    }



     {
        string s="123 456 789 ";
        string sold="456";
        string snew="AAAA";
        replaceString0(s,sold,snew);
        cout << s <<endl;
    }
   
    while(1);


    return 0;
}
