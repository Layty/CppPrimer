#include <iostream>

int main(int argc, char const *argv[])
{
    int i = 0;
    ++(i = 3);
    std::cout << i << std::endl;

    while (1)
        ;
    return 0;
}
