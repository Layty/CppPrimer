// 17.18 修改你的程序，忽略包含“ei”但并非拼写错误的单词，如“albeit”和“neighbor”
// 17.17更新你的程序，令它查找输入序列中所有违反"ei"语法规则的单词。
// 17.5 编写程序，使用模式查找违反“i在e之前，除非在c之后”规则的单词。

//这是一条拼写规则，即通常拼写单词时i在e前，
//除非i前出现了c（这时相反即i在e后）：
//如 believe, receive
// 也就是要查找 [^c]ei单词,但是前面不是c的 合法

#include <regex>
#include <string>
#include <iostream>
#include <exception>
#include <algorithm>
using namespace std;
int main(int argc, const char **argv)
{
    std::vector<std::string> vec{"albeit", "neighbor"};

    regex reg;
    try
    {
        reg.assign("[[:alpha:]]*(cie|[^c]ei)[[:alpha:]]*"); // 这里不去研究正则的内部
    }
    catch (const regex_error &e)
    {
        std::cout << e.what() << ": " << e.code() << std::endl;
    }

    string input;

    while (std::cout << "pls input" << std::endl, getline(cin, input))
    {

        for (sregex_iterator it(input.begin(), input.end(), reg), end_it; it != end_it; ++it)
        {
            if (find(vec.begin(), vec.end(), it->str()) != vec.end())
                continue;
            cout << "Err: " << it->str() << endl;
        }
    }

    return 0;
}