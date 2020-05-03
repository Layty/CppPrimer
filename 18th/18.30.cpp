// 18.30 在Base中定义一个默认构造函数、一个拷贝构造函数和一个接受int形参的构造函数。
// 在每个派生类中分别定义这三种构造函数，每个构造函数应该使用它的形参初始化其Base部分。
#include <iostream>

using namespace std;

class Class
{
public:
    Class() { cout << "class()" << endl; }
};

class Base : public Class
{
public:
    // Base() = default;
    Base() { cout << "Base()" << endl; }
    Base(int) { cout << "Base(int)" << endl; }
    Base(const Base &b) {}
};

class D1 : virtual public Base
{
public:
    D1() = default;
    D1(int i) : Base(i) { cout << "D1(int)" << endl; }
    D1(const D1 &d) {}
};

class D2 : virtual public Base
{
public:
    D2() = default;
    D2(int i) : Base(i) { cout << "D2(int)" << endl; }
    D2(const D2 &d) {}
};

class MI : public D1, public D2
{
public:
    MI() = default;
    MI(int i) : D1(i), D2(i) { cout << "MI(int)" << endl; }
    MI(const MI &m) {}
};

class Final : public MI, public Class
{
public:
    Final() = default;
    // Final(int i) : MI(i) { cout << "Final(int)" << endl; }
    Final(int i) : MI(i), Base(i) { cout << "Final(int)" << endl; }
    Final(const Final &f) {}
};

int main(int argc, char const *argv[])
{
    Final f(1);
    // class()
    // Base(int)
    // D1(int)
    // D2(int)
    // MI(int)
    // class()
    // Final(int)
    while (1)
        ;

    return 0;
}