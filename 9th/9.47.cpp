/*
编写程序，首先查找string "ab2c3d7R4E6"中的每个数字字符，然后查找其中每个字母字符。编写两个版本的程序，第一个要使用find_fisrt_of，第二个要使用 find_first_not_of
*/
#include "include.h"
void find1(const string& s)
{
    string number("0123456789");
    string abc;
    for(int i=0;i<26;i++)
    {
        abc.push_back('a'+i);
        abc.push_back('A'+i);
    }

    string::size_type pos=0;
    while( (pos=s.find_first_of(number,pos)) != string::npos)
    {
        cout << s[pos]<<endl;
        pos++;        
    }

    pos=0;
    while( (pos=s.find_first_of(abc,pos)) != string::npos)
    {
        cout << s[pos]<<endl;
        pos++;        
    }

    //----------------------------------------------------------
    pos=0;
    while( (pos=s.find_first_not_of(number,pos)) != string::npos)
    {
        cout << s[pos]<<endl;
        pos++;        
    }

    pos=0;
    while( (pos=s.find_first_not_of(abc,pos)) != string::npos)
    {
        cout << s[pos]<<endl;
        pos++;        
    }


}




int main(int argc, char const *argv[])
{
    find1("123ABC456");
    while(1);
    return 0;
}
