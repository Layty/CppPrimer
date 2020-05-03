#include <iostream>
using namespace std;

class A
{
public:
    A() { std::cout << "A()" << std::endl; }
};

class B : public A
{
public:
    B() { std::cout << "B()" << std::endl; }
};
class C : public virtual A
{
public:
    C() { std::cout << "C()" << std::endl; }
};

class D : public B, public C
{
public:
    D() { std::cout << "D()" << std::endl; }
};

int main(int argc, const char **argv)
{
    D d;

    // A()  当B不是 virtual 的时候 A还是会两次,也就是说不会自动失败虚基类
    // A()
    // B()
    // C()
    // D()

    while (1)
    {
        /* code */
    }

    return 0;
}
