/*
编写程序，使用fill_n将一个序列中的int都设置为0
*/

#include "include.h"

int main(int argc, char const *argv[])
{

    vector<int> v = {1, 2, 3, 4, 5, 6, 7};

    fill_n(v.begin(), v.size(), 0);
    print(v);
    while (1)
        ;
    return 0;
}
