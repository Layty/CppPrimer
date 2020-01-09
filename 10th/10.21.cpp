/*
编写一个lambda，捕获一个局部int变量，并递减变量值，直至它变为0.一旦变为0，再调用lambda应该不再递减变量。lambda应该返回一个bool值，指出捕获的变量是否为0.
*/
#include "include.h"

int main(int argc, char const *argv[])
{
    int z = 3;

    //auto f = [&z]() {if(z)z--; return(z?false:true); };
    // 也可以使用尾置返回
    auto f = [&z]() -> int {if(z)z--; return(z?false:true); };

    while (z)
    {
        f();
        cout << z << endl;
    }
    while (1)
        ;
    return 0;
}
