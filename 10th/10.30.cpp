/*使用流迭代器、sort和copy从标准输入读取一个整数序列，将其排序，并将结果写到标准输出
*/
#include "include.h"
#include <iterator>

int main(int argc, char const *argv[])
{
    istream_iterator<int> in(cin), eof;
    ostream_iterator<int> out(cout, ",");
    vector<int> v(in, eof);
    sort(v.begin(), v.end());
    copy(v.begin(), v.end(), out);

    while (1)
        ;
    return 0;
}
