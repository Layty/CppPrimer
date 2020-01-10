/*
修改前一题的程序，使其只打印不重复的元素。你的程序应使用unique_copy
*/

#include "include.h"
#include <iterator>

int main(int argc, char const *argv[])
{
    istream_iterator<int> in(cin), eof;
    ostream_iterator<int> out(cout, ",");
    vector<int> v(in, eof);
    sort(v.begin(), v.end());
    //_copy(v.begin(), v.end(), out);
    unique_copy(v.begin(), v.end(), out);

    while (1)
        ;
    return 0;
}