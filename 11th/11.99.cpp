#include "../include/include.h"

// 将s分隔成多个整体（整数、小数、运算符、括号中的部分均算作一个整体）
std::vector<std::string> split(const std::string &s)
{
    std::vector<std::string> ret;
    if (s.length() == 0)
        return ret;
    // bracket
    if (s.at(0) == '(')
    {
        int cnt = 0;
        for (int i = 0; i < s.length(); i++)
        {
            if (s.at(i) == '(')
                cnt++;
            else if (s.at(i) == ')')
                cnt--;
            if (cnt == 0)
            {
                ret.push_back(s.substr(0, i + 1));
                auto r = split(s.substr(i + 1));
                std::copy(r.begin(), r.end(), std::back_inserter(ret));
                break;
            }
        }
    }
    // number
    else if (('0' <= s.at(0) && s.at(0) <= '9') || s.at(0) == '.')
    {
        ret.push_back("");
        for (int i = 0; i < s.length(); i++)
        {
            if (('0' <= s.at(i) && s.at(i) <= '9') || s.at(i) == '.')
                ret.back() += s.at(i);
            else
            {
                auto r = split(s.substr(i));
                std::copy(r.begin(), r.end(), std::back_inserter(ret));
                break;
            }
        }
    }
    // operator
    else
    {
        ret.push_back(s.substr(0, 1));
        auto r = split(s.substr(1));
        std::copy(r.begin(), r.end(), std::back_inserter(ret));
    }
    return ret;
}

// 支持s中含有括号、小数、整数、加号、减号
double calc(std::string s)
{
    auto parts = split(s);
    if (parts.size() == 0)
        return 0;
    if (parts.size() == 1)
    {
        // 如果给定字符串是括号括起来的表达式
        if (s.at(0) == '(')
            return calc(s.substr(1, s.length() - 2));
        else
        {
            //assert(('0' <= s.at(0) && s.at(0) <= '9') || s.at(0) == '.');
            // stod函数是c++11标准支持的，需要编译器不能太老
            return std::stod(s);
        }
    }
    double ret = calc(parts.at(0));
    for (int i = 1; i < parts.size(); i += 2)
    {
        //assert(i + 1 < parts.size());
        if (parts.at(i) == "+")
            ret += calc(parts.at(i + 1));
        else if (parts.at(i) == "-")
            ret -= calc(parts.at(i + 1));
        //else
        //assert(false);
    }
    return ret;
}
int main(int argc, char *argv[])
{

    std::string s;
    std::cin >> s;
    double ans = calc(s);
    if (s.find(".") == std::string::npos)
        std::cout << (long long)ans << std::endl;
    else
        printf("%.6f\n", ans);

    while (1)
        ;
    return 0;
}
