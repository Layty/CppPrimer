// 17.11 定义一个数据结构，包含一个整型对象，记录一个包含10个问题的真/假测验的解答。如果测验包含100道题，你需要对数据结构做出什么改变（如果需要的话）？ 100/8=12.5

#include <bitset>

template <unsigned N>
class quiz
{
public:
    quiz(std::string &s) : bset(s) {}

private:
    std::bitset<N> bset;
};

int main()
{
    std::string s1("0101010101");
    std::string s2("0101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101");
    quiz<10> q1(s1);
    quiz<100> q2(s2);
    while (1)
        ;

    return 0;
}