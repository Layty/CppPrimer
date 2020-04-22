#include <iostream>
#include <typeinfo>
// 右值引用
template <typename T>
void fun(T &&val)
{
    std::cout << val << std::endl;
}

template <typename F, typename T1, typename T2>
// flip2(g, double(i), 42);
/*
    T1 double&  -------  t1 double&
    T2 int      -------  t2 int&&
*/
void flip2(F f, T1 &&t1, T2 &&t2)
{
    // 我理解 这里 t2 是int&& ?  而编译器提示实际这里是int ?
    //
    // int &&a=42;
    // int &&b=a; //非法的,a是变量,是左值,是持久的
    // 注意:------------------------------下面的t2是 函数的参数,参数都是左值表达式,p472

    f(t2, t1);
    //实例化的时候为
    //  g(int &&i, double &j)
}
void g(int &&i, double &j)
{
    std::cout << i << "," << j << std::endl;
}

int main(int argc, char const *argv[])
{
    double i = 33;

    flip2(g, i, 42);

    while (1)
        ;
    return 0;
}
