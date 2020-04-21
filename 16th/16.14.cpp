// 16.14 编写Screen类模版,用非类型参数定义Screen的高和宽,可以当宏使用
#include <string>
#include <algorithm>
#include <iostream>

//using pos = int;
using pos = std::string::size_type;

template <pos, pos>
class Screen;

template <pos H, pos W>
std::istream &operator>>(std::istream &, Screen<H, W> &);

template <pos H, pos W>
std::ostream &operator<<(std::ostream &, const Screen<H, W> &);

template <pos H, pos W>
class Screen
{

    friend std::istream &operator>><H, W>(std::istream &, Screen<H, W> &);
    friend std::ostream &operator<<<H, W>(std::ostream &, const Screen<H, W> &);

private:
    pos curr = 0;
    std::string contents;

public:
    Screen() = default;
    Screen(char c) : contents(H * W, c) {}
    char get() const { return contents[curr]; }
    char get(pos a, pos b) const { return contents[a * W + b]; }
    Screen &set(char c)
    {
        contents[curr++] = c;
        curr = std::min(curr, H * W);
        return *this;
    }
    Screen &set(pos a, pos b, char c)
    {
        contents[a * W + b] = c;
        return *this;
    }
    Screen &move(pos a, pos b);
};

template <pos H, pos W>
Screen<H, W> &Screen<H, W>::move(pos a, pos b)
{
    curr = a * W + b;
    return *this;
}

template <pos H, pos W>
std::istream &operator>>(std::istream &is, Screen<H, W> &s)
{
    std::string input;
    is >> input;
    for (char ch : input)
        s.set(ch);
    return is;
}
template <pos H, pos W>
std::ostream &operator<<(std::ostream &os, const Screen<H, W> &s)
{
    for (pos r = 0; r != H; ++r)
    {
        for (pos c = 0; c != W; ++c)
        {
            os << s.get(r, c);
        }
        os << std::endl;
    }
    return os;
}

int main()
{
    Screen<5, 5> screen('x');
    screen.set(2, 2, 'o');
    std::cout << screen << std::endl;

    std::cout << "please input some characters as you like:";
    std::cin >> screen;
    std::cout << screen << std::endl;
    while (1)
        ;
    {
        /* code */
    }
}

// xxxxx
// xxxxx
// xxoxx
// xxxxx
// xxxxx

// please input some characters as you like:1234512345123451234512345999
// 12345
// 12345
// 12345
// 12345
// 12345