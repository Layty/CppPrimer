/* 14.44 实现2元简单计算器
    // 这里测试是用 1 + 2  而不是 1+2 否则是
    terminate called after throwing an instance of 'std::bad_function_call'
    what():  bad_function_call
*/

#include <functional>
#include <algorithm>
#include <string>
#include <map>
#include <iostream>

int add(int a, int b)
{
    return a + b;
}

auto mod = [](int a, int b) {
    return a % b;
};

struct mdiv
{
    int operator()(int a, int b)
    {
        return a / b;
    }
};

std::map<std::string, std::function<int(int, int)>> binops =
    {
        {"+", add},
        {"-", std::minus<int>()},
        {"/", mdiv()},
        {"*", [](int a, int b) { return a * b; }},
        {"%", mod}};

int main(int argc, const char **argv)
{
    try
    {
        while (true)
        {
            std::cout << "\nplease enter: num operator num :\n";
            int n1, n2;
            std::string s;
            std::cin >> n1 >> s >> n2;

            std::cout << binops[s](n1, n2) << std::endl;
            ;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    while (1)
    {
        /* code */
    }

    return 0;
}