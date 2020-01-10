/*
编写程序，接受三个参数：一个输入文件和两个输出文件的文件名。输入文件保存的应该是整数。
使用istream_iterator读取输入文件。使用ostream_iterator将奇数写入第一个输出文件，每个值之后都跟一个空格。
将偶数写入第二个输出文件，每个值都独占一行
*/

#include "include.h"
#include <fstream>
#include <iterator>

int main(int argc, char const *argv[])
{
    const char *path = "D:\\0.txt";
    const char *path1 = "D:\\1.txt";
    const char *path2 = "D:\\2.txt";

    ifstream fin(path);
    ofstream fout1(path1);
    ofstream fout2(path2);

    if (!fin)
        cout << "open" << path << "faile" << endl;
    if (!fout1)
        cout << "open" << path1 << "faile" << endl;
    if (!fout2)
        cout << "open" << path2 << "faile" << endl;
    if (!fin || !fin || !fout2)
        while (1)
            ;

    istream_iterator<int> in(fin), iof;
    ostream_iterator<int> o1(fout1, " ");
    ostream_iterator<int> o2(fout2, "\n");

    while (in != iof)
    {

        cout << *in << endl;
        if (*in & 0x01)
        {
            *o1++ = *in;
        }
        else
        {
            *o2++ = *in;
        }
        in++;
    }

    fout1.close();
    fout2.close();
    while (1)
        ;
    return 0;
}
