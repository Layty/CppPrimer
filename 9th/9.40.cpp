#include "include.h"

template<typename T>
void printInfo(const T& v)
{
    cout <<"size="<<v.size()<<endl;
    cout <<"capacity="<<v.capacity()<<endl;
}


int main(int argc, const char** argv) {

    vector<string> svec;
    svec.reserve(1024);
    string word;

    for(int i=0;i<1000;i++){
        svec.push_back("123");
    }
    svec.resize(svec.size() + svec.size()/2);
    printInfo(svec);//size=1500 capacity=2000


    vector<string> svec2;
    svec2.reserve(1024);
    for(int i=0;i<1500;i++){
        svec2.push_back("123");
    }
    printInfo(svec2);//size=1500 capacity=2000
 
    while(1);
    return 0;
}