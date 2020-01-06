/*
    从vector<char> 创建 string
*/
#include "include.h"


int main(int argc, char const *argv[])
{
    vector<char> vstr={'1','2','3','\0'};

    string s(vstr.begin(),vstr.end());
    cout<<s<<endl;
    while(1);
    return 0;
}
