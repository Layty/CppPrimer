#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
int main(int argc, char const *argv[])
{
    int a = 6;
    double b = 6.1231;
    std::cout << std::max<long double>(a, b) << std::endl;
    // initializer_list<T> 也是模版,不会发生转换
    //std::cout << std::max({a, b}, [](const int a, const int b) { return a < b; }) << std::endl;
    std::cout << std::max({1, 2}, [](const int a, const int b) { return a < b; }) << std::endl;

    while (1)
        ;
    return 0;
}
