// 16.50 定义上一个练习中的函数，令它们打印一条身份信息。运行该练习中的代码。如果函数调用的行为与你预期不符，确定你理解了原因。
/*
template <typename T> void f(T);
template <typename T> void f(const T*);
template <typename T> void g(T);
template <typename T> void g(T*);
int i = 42, *p = &i;
const int ci = 0, *p2 = &ci;
g(42); g(p); g(ci); g(p2);
f(42); f(p); f(ci); f(p2);


g(42)   T=int  			3.template <typename T> void g(T);
g(p) 	T=int			4.template <typename T> void g(T*);
g(ci)	T=const int		3.template <typename T> void g(T);
g(p2)	T=const int		4.template <typename T> void g(T*);

f(42)	T=int			1.template <typename T> void f(T);
f(p)	T=int*			1.template <typename T> void f(T);
f(ci)	T=const int		1.template <typename T> void f(T);
f(p2)   T=int			2.template <typename T> void f(const T*);
*/
#include <iostream>
#include <string>

template <typename T>
void f(T)
{
    std::cout << "1" << std::endl;
}
template <typename T>
void f(const T *)
{
    std::cout << "2" << std::endl;
}
template <typename T>
void g(T)
{
    std::cout << "3" << std::endl;
}
template <typename T>
void g(T *)
{
    std::cout << "4" << std::endl;
}

int main(int argc, char const *argv[])
{
    int i = 42, *p = &i;
    const int ci = 0, *p2 = &ci;
    g(42);
    g(p);
    g(ci);
    g(p2);
    f(42);
    f(p);
    f(ci);
    f(p2);

    while (1)
        ;
    return 0;
}
