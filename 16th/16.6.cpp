//16.6 	你认为一个接受数组实参的标准库函数 begin 和end是如何工作的,定义你自己版本的begin和end
// 		也就是定义 begin(array)和end(array)
#include <iostream>
#include <string>
template <typename elem_type, size_t size>
elem_type *Begin(elem_type (&array)[size])
{
    return array;
}

template <typename elem_type, size_t size>
elem_type *End(elem_type (&array)[size])
{
    return array + size;
}

int main(int argc, char const *argv[])
{
    std::string as[] = {"123", "456", "789"};

    for (auto i = Begin(as); i != End(as); i++)
        std::cout << *i << std::endl;

    while (1)
        ;
    return 0;
}