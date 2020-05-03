#include <iostream>
#include <typeinfo>
using namespace std;
class A
{
};
class B : public A
{
};
class C : public B
{
};

int main(int argc, char const *argv[])
{
    {
        A *pa = new C; //A类型指针 P1A
        cout << typeid(pa).name() << endl;
    }
    {
        C cobj;
        A &ra = cobj;
        cout << typeid(&ra).name() << endl; //A类型指针 P1A
    }
    {
        B *px = new B;
        A &ra = *px;
        cout << typeid(ra).name() << endl; // A类型 1A
    }

    while (1)
        ;
    return 0;
}
