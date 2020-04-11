/*
14.36 保存到vector
14.35 编写一个类似PrintString的类，令其从istream中读取一行输入，然后返回一个表示我们所读内容的string。如果读取失败，返回空string
*/

#include <iostream>
#include <string>
#include <vector>

class PrintStringLine
{
public:
    std::string operator()(std::istream &in)
    {
        std::string line;
        if (getline(in, line))
            return line;
        else
            return std::string();
    }
};

int main(int argc, char const *argv[])
{
    PrintStringLine p;
    //std::cout << "--" << p(std::cin) << "--" std::endl;

    std::vector<std::string> v;
    // v.push_back(p(std::cin));
    // v.push_back(p(std::cin));
    // v.push_back(p(std::cin));
    // v.push_back(p(std::cin));
    // v.push_back(p(std::cin));

    for (std::string tmp; !(tmp = PrintStringLine()(std::cin)).empty();)
        v.push_back(tmp);

    for (auto ch : v)
        std::cout << "~" << ch << "~" << std::endl;

    while (1)
        ;
    return 0;
}
