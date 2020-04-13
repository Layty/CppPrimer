// 16.4 编写行为类似标准库find算法的模版.函数需要两个模版类型参数,一个表示函数的迭代器参数,另一个表示值的类型.
//      使你的函数在一个vector<int> 和 list<string>中查找给定值

#include <vector>
#include <list>
#include <string>
#include <iostream>

template <typename it_type, typename value_type>
it_type find(const it_type begin, const it_type end, const value_type val)
{
    for (auto it = begin; it != end; it++)
    {
        if (*it == val)
            return it;
    }
    return end;
}

template <typename it_type, typename value_type>
std::ostream &PrintFind(const it_type &begin, const it_type &end, const value_type &val, std::ostream &o = std::cout)
{
    it_type find_it = find(begin, end, val);
    if (find_it == end)
        return o << "Null to find";
    else
        return o << *find_it;
}

int main(int argc, char const *argv[])
{
    std::vector<int> vs({1, 2, 3, 4, 5, 6, 7, 8, 9});

    std::cout << *find(vs.begin(), vs.end(), 2) << std::endl;
    PrintFind(vs.begin(), vs.end(), 2) << std::endl;
    PrintFind(vs.begin(), vs.end(), 10) << std::endl;

    std::list<std::string> ls({"123", "456", "ABC"});
    PrintFind(ls.begin(), ls.end(), "999") << std::endl;

    while (1)
        ;
    return 0;
}
