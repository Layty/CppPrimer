/*
lamdda 接收两个int 返回sum
*/

#include "include.h"
int main(int argc, char const *argv[])
{

    auto f = [](const int a, const int b) { return a + b; };

    cout << f(1, 2) << endl;

    while (1)
        ;
    return 0;
}
