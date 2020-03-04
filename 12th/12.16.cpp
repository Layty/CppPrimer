/*
12.16 给一个unique_ptr 赋值观察错误
*/
#include <iostream>
#include <memory>
using namespace std;

int main(int argc, char const *argv[])
{
    unique_ptr<int> p(new int(3));
    int *pint = new int(3);
    unique_ptr<int> p_unique(new int(3));

    //unique_ptr<int> s(3);

    // no known conversion for argument 1 from 'int*' to 'std::nullptr_t'
    //p = pint;

    // use of deleted function 'std::unique_ptr<_Tp, _Dp>& std::unique_ptr<_Tp, _Dp>::operator=(const std::unique_ptr<_Tp, _Dp>&) [with _Tp = int; _Dp = std::default_delete<int>]'
    //unique_ptr& operator=(const unique_ptr&) = delete;
    //p = p_unique;

    while (1)
        ;
    return 0;
}
