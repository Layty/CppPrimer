/*假定vi是一个保存int的容器，其中有偶数值也要奇数值，分析下面循环的行为，然后编写程序验证你的分析是否正确。*/



#include "include.h"

int main(int argc, const char** argv) {
 
    vector<int> v1={1,2,3,4,5,6,7,8,9};

    auto iter=v1.begin();
    while(iter!=v1.end())
    {
        if(*iter%2)
        {
            iter=v1.insert(iter,*iter);
            // ++iter;  ///-----if里面也需要++一次
        }
        ++iter;
    }
    print(v1);
    while(1);
    return 0;
}