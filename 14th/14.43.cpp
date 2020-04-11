/*
14.43：使用标准库函数对象判断一个给定的int值是否能被int容器中的所有元素整除
*/

#include <algorithm>
#include <iostream>
#include <vector>
#include <functional>
using namespace std::placeholders;

bool IfDivVec(int a, std::vector<int> &v)
{
    auto w = std::find_if(v.cbegin(), v.cend(), std::bind(std::modulus<int>(), _1, a));
    return w == v.cend();
}

int main(int argc, char const *argv[])
{
    int a = 3;
    std::vector<int> v = {3, 6, 9, 18, 24};
    std::cout << std::boolalpha << IfDivVec(a, v) << std::endl;

    v.push_back(13);
    std::cout << std::boolalpha << IfDivVec(a, v) << std::endl;
    while (1)
        ;

    return 0;
}

// auto data = {2, 3, 4, 5};
// int input;
// std::cin >> input;
// std::modulus<int> mod;
// auto predicator = [&](int i) { return 0 == mod(input, i); };
// auto is_divisible = std::any_of(data.begin(), data.end(), predicator);
// std::cout << (is_divisible ? "Yes!" : "No!") << std::endl;
