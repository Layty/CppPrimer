// 16.5 编写一个printf 支持任意大小任意元素类型的数组

#include <iostream>
#include <string>
template <typename elem_type, int size>
void print(elem_type (&arr)[size])
{
    for (auto ch : arr)
    {
        std::cout << ch << std::endl;
    }
}
int main(int argc, char const *argv[])
{
    std::string as[] = {"123", "456", "789"};
    int ai[] = {1, 2, 3, 4, 5, 6};
    print(as);
    print(ai);
    while (1)
        ;
    return 0;
}
