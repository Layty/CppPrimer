// 17.10使用序列1、2、3、5、8、13、21初始化一个bitset，将这些位置置位。对另一个bitset进行默认初始化，并编写一小段程序将其恰当的位置位

#include <bitset>
#include <vector>
#include <iostream>
using namespace std;
int main(int argc, const char **argv)
{
    std::bitset<32> b32;
    std::vector<int> v = {1, 2, 3, 8, 13, 21};
    for (auto ch : v)
        b32.set(ch);
    std::cout << b32 << std::endl;
    while (1)
        ;
    return 0;
}