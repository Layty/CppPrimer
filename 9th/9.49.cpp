/*
如果一个字母延伸要中线之上，如d或f，则称其有上出头部分。如果延伸到中线之下，则称其有下出头部分。编写程序，读入一个单词文件，输出最长的既不包含上出头部分，也不包含下出头部分的单词。
*/
#include <fstream>
#include "include.h"

int main(int argc, char const *argv[])
{
    ifstream file("E:\\Reading\\C++\\C+++Primer\\CppPrimer-master\\CppPrimer-master\\ch09\\ex9_49.cpp");
    if(!file) 
    {
        cout << "file open filed"<<endl;
        while(1);
        return -1;
    }

    string s;
    string get;
    while(file>>s)
    {
        if(s.find_first_not_of("aceimnorsuvwxz")==string::npos)
        {
            if(get.size()<s.size())
                get=s;
        }
    }
    cout << "get: "<<get <<endl;

    while(1);
    return 0;
}
