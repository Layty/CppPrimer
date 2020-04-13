// 16.2 编写你自己的compare版本

#include <iostream>

template <typename T>
int compare(const T &a, const T &b)
{
    if (a > b)
        return 1;
    if (a < b)
        return -1;
    return 0;
}

int main(int argc, char const *argv[])
{
    std::cout << compare(1, 2) << std::endl;
    while (1)
        ;
    return 0;
}
