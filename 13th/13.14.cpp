#include <iostream>
using namespace std;

class Num
{
public:
    static int t;
    Num() : me(t++) {}
    //Num(const Num &s) : me(s.t++) {}
    int me;
};
int Num::t = 0;

void f(Num s)
{
    cout << s.me << endl;
}

int main(int argc, const char **argv)
{

    Num a, b = a, c = b;
    f(a);
    f(b);
    f(c);
    while (1)
    {
        /* code */
    }

    return 0;
}
//0,0,0