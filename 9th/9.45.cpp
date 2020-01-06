/*
9.45
接受一个表示名字的string参数和两个分别表示前缀（如“Mr."或”Ms.“）和后缀（Jr或III）的字符串。\
使用迭代器及insert和append函数将前缀和后缀加到给定的名字中，将生成的新string返回。

9.46
重写上一题的函数，这次使用位置和长度来管理string，并只使用insert
 */

#include "include.h"


string fullName(const string& s,const string& before,const string& after)
{
    string full(s);
    full.insert(full.begin(),before.begin(),before.end());
    full.append(after);
    return full;
}


string fullName2(const string& s,const string& before,const string& after)
{
    string full(s);
    full.insert(0,before);
    full.insert(full.size(),after);
    return full;
}




int main(int argc, char const *argv[])
{

    cout << fullName("layty","Mr."," good")<<endl;
    cout << fullName2("layty","Mr."," good")<<endl;

    while(1);
    return 0;
}
