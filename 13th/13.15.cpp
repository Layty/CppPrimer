#include <iostream>
using namespace std;

class Num
{
public:
    static int t;
    Num() : me(t++) {}
    Num(const Num &s) : me(s.t++) {}
    int me;
};
int Num::t = 0;

void f(const Num &s)
{
    cout << s.me << endl;
}

int main(int argc, const char **argv)
{
    // 结果是3,4,5
    Num a, b = a, c = b; //0,1,2
    f(a);                // 说明这里发生了拷贝构造,实参传递的时候,如果这里是传递引用,则不会发生拷贝构造,结果是0,1,2
    f(b);
    f(c);
    while (1)
    {
        /* code */
    }

    return 0;
}
//3,4,5