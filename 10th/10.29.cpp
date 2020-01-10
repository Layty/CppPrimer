/*
编写程序，使用流迭代器读取一个文本文件，存入一个vector中的string里
 1:  vector<string> v(in_iter, eof_f);
 2: copy(in_iter, eof_f, back_inserter(vec));

*/
#include <fstream>
#include <iterator>

#include "include.h"

int main(int argc, char const *argv[])
{

    ifstream in_f("E:\\Reading\\C++\\C+++Primer\\CppPrimer-master\\CppPrimer\\10th\\10.29.cpp");
    istream_iterator<string> in_iter(in_f);
    istream_iterator<string> eof_f;

    // 方式1
    vector<string> v(in_iter, eof_f);
    for_each(v.begin(), v.end(), [](const string &ch) { cout << ch << endl; });

    //方式2
    vector<string> vec;
    copy(in_iter, eof_f, back_inserter(vec));
    std::copy(v.cbegin(), v.cend(), std::ostream_iterator<string>(std::cout, "\n"));

    while (1)
        ;
    return 0;
}
