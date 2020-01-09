/*
编写一个lambda，捕获它所在函数的int，并接受一个int参数。lambda应该返回捕获的int和int参数的和
*/
#include "include.h"

int main(int argc, char const *argv[])
{
    int a = 1;
    auto f = [a](int b) { return a + b; };
    cout << f(3) << endl;
    while (1)
        ;
    return 0;
}
