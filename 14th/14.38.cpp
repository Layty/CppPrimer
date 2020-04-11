/*
14.39 修改其报告1~9的单词有几个,10以上的有几个
14.38 编写一个类令其检查某个给定的string对象的长度是否与一个阀值相等。使用该对象编写程序，统计并报告在输入的文件中长度为1的单词有多少个、长度为2的单词有多少个。
*/

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
class StrLen
{
private:
    int len;
    bool cmp;

public:
    StrLen(int l, bool cmp = false) : len(l), cmp(cmp) {}
    bool operator()(const std::string &s)
    {
        if (cmp == false)
            return s.size() == len;
        else
            return s.size() >= len;
    }
};

int main(int argc, char const *argv[])
{
    std::string path = "D:\\1.txt";
    std::ifstream infile(path);
    if (!infile)
    {
        std::cout << "err to open path" << path << std::endl;
        while (1)
            ;
    }

    std::string s;
    std::vector<std::string> v;
    int len_1 = 0, len_2 = 0, len_10_big = 0, len_10_lit = 0;
    StrLen l2(2);
    StrLen l1(1);
    StrLen l10(10, true);

    while (infile >> s)
    {
        //v.push_back(std::move(s));
        if (l1(s))
            len_1++;

        if (l2(s))
            len_2++;
        if (l10(s))
            len_10_big++;
        else
            len_10_lit++;
    }
    std::cout << "len=1,count=" << len_1 << std::endl;
    std::cout << "len=2,count=" << len_2 << std::endl;
    std::cout << "len>=10,count=" << len_10_big << std::endl;
    std::cout << "len<10>,count=" << len_10_lit << std::endl;
    while (1)
        ;

    return 0;
}
