//15.23 假设第550页的 D1 类需要覆盖它继承而来的 fcn 函数，你应该如何对其进行修改？  -- 这里是虚函数的覆盖,要改变参数类型为void,然后加overide检查
//      如果你修改之后 fcn 匹配了 Base 中的定义，则该节的那些调用语句将如何解析？

//  http://stackoverflow.com/questions/21320779/trying-to-understand-dynamic-binding-and-virtual-functions

#include <iostream>
#include <string>

class Base
{
public:
    virtual int fcn()
    {
        std::cout << "Base::fcn()\n";
        return 0;
    }
};

class D1 : public Base
{
public:
    int fcn() override
    {
        std::cout << "D1::fcn()\n";
        return 0;
    }
    //! ^^^--fixed to override the inherited version
    virtual void f2() { std::cout << "D1::f2()\n"; }
};

class D2 : public D1
{
public:
    int fcn(int);
    int fcn() override
    {
        std::cout << "D2::fcn()\n";
        return 0;
    }
    void f2() override { std::cout << "D2::f2()\n"; }
};

int main()
{
    Base bobj;
    D1 d1obj;
    D2 d2obj;

    Base *bp1 = &bobj, *bp2 = &d1obj, *bp3 = &d2obj;
    // 基类的fcn 是虚函数了,所以都是动态绑定
    //bp1->fcn(); //! virtual call, will call Base::fcn at run time
    //bp2->fcn(); //! virtual call, will call D1::fcn   at run time
    //bp3->fcn(); //! virtual call, will call D2::fcn   at run time

    D1 *d1p = &d1obj;
    D2 *d2p = &d2obj;

    // 父类没有这个方法,虽然是动态绑定,但是动态绑定的第一步是指针有这个方法
    //bp2->f2();
    //!^^^^^^^^^^^^
    //! @note   You are calling virtual member functions via a pointer
    //! to Base. That means that you can only call methods that exist
    //! in the Base class. You cannot simply add methods to a type
    //! dynamically.
    // 虚函数是从子类开始的,所以后续可以动态绑定了
    d1p->f2(); //! virtual call, will call D1::f2() at run time
    d2p->f2(); //! virtual call, will call D2::f2() at run time

    return 0;
}
