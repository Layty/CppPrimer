/*
14.37 编写一个类令其检查两个值是否相等。使用该对象及标准库算法编写程序，令其替换某个序列中具有给定值的所有实例
*/
#include <vector>
#include <algorithm>
#include <iostream>

class Equal
{
private:
    int data;

public:
    Equal(int c) : data(c) {}
    bool operator()(int a) { return a == data; }
};

int main(int argc, char const *argv[])
{
    std::vector<int> v = {1, 2, 3, 4, 5, 6, 2, 3, 2, 1, 4, 6, 7, 8, 1, 2, 3, 1};
    std::replace_if(v.begin(), v.end(), Equal(1), 9999);

    // for (auto ch : v)
    //     std::cout << ch << ",";
    // std::cout << std::endl;

    std::for_each(v.begin(), v.end(), [](std::vector<int>::value_type c) { std::cout << c << ","; });
    //std::for_each(v.begin(), v.end(), [](int c) { std::cout << c << ","; });

    while (1)
    {
        /* code */
    }

    return 0;
}
