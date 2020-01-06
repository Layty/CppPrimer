/**
    编写程序，探究在你的标准库实现中，vector是如何增长的
 */

#include "include.h"


void printInfo(vector<int> &v)
{
    cout <<"size="<<v.size()<<endl;
    cout <<"capacity="<<v.capacity()<<endl;
}

int main(int argc, const char** argv) {
 
    vector<int> v1;
    printInfo(v1);      //size=0,capacity=0

    v1.push_back(1);    //size=1,capacity=1
    printInfo(v1);      

    v1.push_back(1);    //size=2,capacity=2
    printInfo(v1);

    v1.push_back(1);    //size=3,capacity=4
    printInfo(v1);


    while(1);
    return 0;
}