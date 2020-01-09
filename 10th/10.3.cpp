/*用accumulate求一个vector中的元素之和*/
/*假定v是一个vector, 那么调用accumulate(v.cbegin(), v.cend(), 0)有何错误（如果存在）*/
#include "include.h"

int main(int argc, char const *argv[])
{
    vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8};

    auto sum = accumulate(v.begin(), v.end(), 0);
    cout << sum << endl;

    vector<double> v2 = {1.1, 1.2};
    auto sum2 = accumulate(v2.begin(), v2.end(), (double)0); //或者0.0都可以
    cout << sum2 << endl;

    while (1)
        ;
    return 0;
}
