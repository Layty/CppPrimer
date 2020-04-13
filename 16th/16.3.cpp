// 16.2 编写你自己的compare版本

#include <iostream>

class Sales_data
{
private:
    int a;

public:
    Sales_data() : a(0) {}
    ~Sales_data() {}
};

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
    Sales_data a;
    Sales_data b;
    std::cout << compare(1, 2) << std::endl;
    std::cout << compare(a, b) << std::endl;
    while (1)
        ;
    return 0;
}