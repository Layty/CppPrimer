#include <iostream>
#include <string>
using namespace std;

class Base
{
public:
    void memfcn(Base &b) { b = *this; };

protected:
    int prot_mem;

private:
    char priv_mem;
};

struct Pub_Derv : public Base
{
public:
    void memfcn(Base &b) { b = *this; };
};

struct Priv_Derv : private Base
{
public:
    void memfcn(Base &b) { b = *this; };
};

struct Prot_Derv : protected Base
{
public:
    void memfcn(Base &b) { b = *this; };
};

struct Derived_from_Public : public Pub_Derv
{
public:
    void memfcn(Base &b) { b = *this; };
};

struct Derived_from_Private : public Priv_Derv
{
public:
    // void memfcn(Base &b) { b = *this; };
};

struct Derived_from_Protected : public Prot_Derv
{
public:
    void memfcn(Base &b) { b = *this; };
};

int main(int argc, char const *argv[])
{
    // 只有当D公有地继承B时，用户代码才能使用派生类向基类的转换。
    Pub_Derv d1;  //public    继承 base
    Priv_Derv d2; //private   继承
    Prot_Derv d3; //protected 继承

    Derived_from_Public dd1;    //公共继承  公共继承的派生类    父->public子->public孙
    Derived_from_Private dd2;   //公共继承  私有继承的派生类    父->private子->public孙
    Derived_from_Protected dd3; //公共继承  公共继承的派生类    父->protected子->public孙

    Base *p = &d1; //d1 的类型是 Pub_Derv       //                    inaccessible=无法访问
                   //p = &d2;       //d2 的类型是 Priv_Derv      //error: 'Base' is an inaccessible base of 'Priv_Derv'
                   //p = &d3;      //d3 的类型是 Prot_Derv       //error: 'Base' is an inaccessible base of 'Prot_Derv'
    p = &dd1;      //dd1 的类型是 Derived_from_Public
                   //p = &dd2;    //dd2 的类型是 Derived_from_Private  //error: 'Base' is an inaccessible base of 'Derived_from_Private'
    //p = &dd3;      //dd3 的类型是 Derived_from_Protected //error: 'Base' is an inaccessible base of 'Derived_from_Protected'
    return 0;
}
