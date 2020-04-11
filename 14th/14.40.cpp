/*
14.40 重写10.3.2的P349 的biggies 函数,使用可调用类替换lambda
*/

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using std::cin;
using std::cout;
using std::endl;
using std::find_if;
using std::for_each;
using std::sort;
using std::stable_sort;
using std::string;
using std::vector;

class WordsABSizeCmp
{
public:
    bool operator()(const string &a, const string &b)
    {
        return a.size() < b.size();
    }
};

class WordsBigThan
{
private:
    int default_size;

public:
    WordsBigThan(int dsize) : default_size(dsize) {}
    bool operator()(const string &a)
    {
        return a.size() >= default_size;
    }
};

void elimdups(vector<string> &words)
{
    sort(words.begin(), words.end());
    auto end_unique = unique(words.begin(), words.end());
    words.erase(end_unique, words.end());
}

string make_plural(size_t ctr, string const &word, string const &ending)
{
    return (ctr > 1) ? word + ending : word;
}

class PrintString
{
private:
    std::ostream &o;

public:
    PrintString(std::ostream &o = std::cout) : o(o) {}
    std::ostream &operator()(const string &s) { return o << s << ","; }
};

void biggies(vector<string> &words, vector<string>::size_type sz)
{
    // 删除重复单词
    elimdups(words);
    // 按照长度排序单词
    stable_sort(words.begin(), words.end(), WordsABSizeCmp());
    // 找到第一个size大于某值的元素
    auto wc = find_if(words.begin(), words.end(), WordsBigThan(sz));
    // 计算size大于某值的数目
    auto count = words.end() - wc;

    cout << count << make_plural(count, "word", "s") << " of length " << sz << "or longer" << endl;
    for_each(wc, words.end(), PrintString());
}

int main()
{
    vector<string> vec{"fox", "jumps", "over", "quick", "red",
                       "red", "slow", "the", "turtle"};
    biggies(vec, 4);
    while (1)
    {
        /* code */
    }
}