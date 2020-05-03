// 17.5 编写程序，使用模式查找违反“i在e之前，除非在c之后”规则的单词。
// 你的程序应该提示用户输入一个单词，然后指出此单词是否符号要求。
// 用一些违反和未违反规则的单词测试你的程序。

// 也就是 合法是 i在e之后

//ie 非法
//cie 但是合法
//[^c]ie 非法
//"[[:alpha:]]*[^c]ei[[:alpha:]]*"
#include <regex>
#include <string>
#include <iostream>
#include <exception>
using namespace std;
int main(int argc, const char **argv)
{
    regex reg;
    try
    {
        //reg.assign("[[:alpha:]]*[^c]ie[[:alpha:]]*");   // 这里没有处理ie开头的
        reg.assign("[[:alpha:]]*(cie|[^c]ei)[[:alpha:]]*"); // 这里不去研究正则的内部
    }
    catch (const regex_error &e)
    {
        std::cout << e.what() << ": " << e.code() << std::endl;
    }

    string input;

    while (std::cout << "pls input" << std::endl, cin >> input)
    {
        smatch ret;
        if (regex_search(input, ret, reg))
        {
            std::cout << "err" << std::endl;
            std::cout << ret.str() << std::endl;
        }
        else
        {
            std::cout << "ok" << std::endl;
        }
    }

    return 0;
}