// 17.13 编写一个整型对象，包含真/假测验的正确答案。使用它来为前两题中的数据结构生成测验成绩。
// 17.12 使用前一题中的数据结构，编写一个函数，它接受一个问题编号和一个表示真/假解答的值，函数根据这两个参数更新测验的解答。//
// 17.11 定义一个数据结构，包含一个整型对象，记录一个包含10个问题的真/假测验的解答。如果测验包含100道题，你需要对数据结构做出什么改变（如果需要的话）？ 100/8=12.5

#include <bitset>
#include <iostream>
#include <string>

using namespace std;

template <unsigned N>
class quiz
{
    template <unsigned M>
    friend ostream &operator<<(ostream &o, const quiz<M> &q);

public:
    quiz(const std::string &s) : bset(s) {}
    quiz(int s) : bset(s) {}
    void set(std::size_t n, bool v) { bset.set(n, v); }
    int score(const quiz &correct)
    {
        return (this->bset ^ correct.bset).flip().count() * 1.0 / N * 100;
    }

private:
    std::bitset<N> bset;
};

template <unsigned M>
ostream &operator<<(ostream &o, const quiz<M> &q)
{
    return o << q.bset << endl;
}

int main()
{
    std::string s1("1111100000");
    quiz<10> q1(s1);
    q1.set(0, 1);

    std::cout << q1 << std::endl;

    std::cout << q1.score(quiz<10>(10)) << std::endl;
    std::cout << q1.score(quiz<10>(string("1111100001"))) << std::endl;
    while (1)
        ;

    return 0;
}