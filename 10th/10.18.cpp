/*
求一个大于等于给定长度的单词有多少,并将其打印出来
void biggiest(vector<string>v,vector<string>::size_type sz)


-------------------------------sort by dic
0,123,1234,99999999999,hello,world,
-------------------------------sort by dic,then stable_sort by len,then use findif
1234,hello,world,99999999999,
-------------------------------sort by dic,then partition
world,hello,1234,99999999999,
-------------------------------sort by dic,then stable_partition
1234,99999999999,hello,world,


*/
#include "include.h"

string make_plural(size_t ctr, const string &word, const string &ending)
{
    return (ctr > 1) ? word + ending : word;
}
void elimdups(vector<string> &words)
{
    sort(words.begin(), words.end());
    auto end_unique = unique(words.begin(), words.end());
    words.erase(end_unique, words.end());
}

void biggiest2(vector<string> &words, vector<string>::size_type sz)
{
    elimdups(words); //将words按字典序排序，删除重复词

    // 获取一个迭代器，指向最后一个满足size()>=sz的元素之后的位置
    auto wc = partition(words.begin(), words.end(), [sz](const string &a) { return a.size() >= sz; });
    // 计算满足size()>=sz的元素的数目
    auto count = wc - words.begin();
    cout << count << " " << make_plural(count, "word", "s") << " of length " << sz << " or longer" << endl;
    // 打印长度大于等于给定值的单词，每个单词后面接一个空格
    for_each(words.begin(), wc, [](const string &s) { cout << s << " "; });
    cout << endl;
}

void biggiest(vector<string> v, vector<string>::size_type sz)
{
    // 按照字典排序,删除重复单词
    sort(v.begin(), v.end());
    auto last = unique(v.begin(), v.end());
    v.erase(last, v.end());

    vector<string> cp1(v);
    vector<string> cp2(v);

    cout << "-------------------------------sort by dic" << endl;
    for_each(cp1.begin(), cp1.end(), [](const string &a) { cout << a << ","; });
    cout << endl;

    cout << "-------------------------------sort by dic,then stable_sort by len,then use findif" << endl;
    // 按照长度排序,这里需要传递一个长度 使用lamada
    stable_sort(v.begin(), v.end(), [](const string &a, const string &b) { return a.size() < b.size(); });
    //找到第一个长度>sz的迭代器
    auto fst = find_if(v.begin(), v.end(), [sz](const string &a) { return a.size() >= sz; });
    // 打印vec
    for_each(fst, v.end(), [](const string &a) { cout << a << ","; });
    cout << endl;

    cout << "-------------------------------sort by dic,then partition" << endl;
    auto lst = partition(cp1.begin(), cp1.end(), [sz](const string &a) { return a.size() >= sz; });
    for_each(cp1.begin(), lst, [](const string &a) { cout << a << ","; });
    cout << endl;

    cout << "-------------------------------sort by dic,then stable_partition" << endl;
    auto lst2 = stable_partition(cp2.begin(), cp2.end(), [sz](const string &a) { return a.size() >= sz; });
    for_each(cp2.begin(), lst2, [](const string &a) { cout << a << ","; });
    cout << endl;
}

int main(int argc, char const *argv[])
{
    vector<string> v = {"0", "123", "1234", "hello", "world", "99999999999", "world"};
    biggiest(v, 4);

    while (1)
        ;
    return 0;
}
