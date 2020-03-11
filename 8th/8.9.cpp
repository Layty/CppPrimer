/*使用8.1.2节第一个练习所编写的函数打印一个istringstream对象的内容*/

/*
编写函数，接受一个istream &参数，返回值也是istream&。此函数必须从给定流中读取数据，直至遇到文件结束标识符时停止。
它将读取的数据打印在标准输出上。完成这些操作后，在返回流之前，对流进行复位，使其处于有效状态。
*/

#include <iostream>
#include <sstream>
using namespace std;

istream &readeof(istream &in)
{
    string s;
    while (in >> s)
    {
        cout << s;
        in.clear();
    }
    cout << endl;
    in.clear();
}

int main(int argc, char const *argv[])
{
    //readeof(cin);
    stringstream ss("1234567");
    readeof(ss);
    cout << "Get EOF" << endl;
    while (1)
        ;
    return 0;
}
