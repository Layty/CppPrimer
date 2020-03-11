/*12.24：编写一个程序，从标准输入读取一个字符串，存入一个动态分配的字符数组中。描述你的程序如何处理变长。测试你的程序，输入一个超出你分配的数组长度的字符串*/

#include <iostream>
using namespace std;

int main(int argc, char const *argv[])
{
    char c;
    char *s = new char[4];
    int i = 0;
    int len = 4;

    while (cin >> c)
    {
        if (i >= len - 1)
        {
            char *s_new = new char[len * 2];
            memcpy(s_new, s, len - 1);
            len *= 2;
            delete[] s;
            s = s_new;
            cout << "before len:" << len / 2 << ",arter len=" << len << " last char is " << s_new[i - 1] << endl;
        }
        if (c == '\r' || c == '\n')
            break;
        s[i++] = c;
    }
    s[i] = 0;
    cout << s << endl;

    while (1)
        ;
    return 0;
}
