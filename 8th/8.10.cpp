/*
8.10 编写程序，将来自一个文件中的行保存在一个vector中，然后使用一个istringstream从vector读取数据元素，每次读取一个单词。
*/

#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char const *argv[])
{
    string filepath = "C:\\JLink.log";
    ifstream in(filepath);

    if (!in)
    {
        cout << "Check File" << endl;
    }

    vector<string> line;
    string s;
    while (getline(in, s))
    {
        line.push_back(s);
    }

    for (auto c : line)
    {
        stringstream ss(c);
        string ch;
        while (ss >> ch)
        {
            cout << ch << endl;
        }
    }

    while (1)
        ;
    return 0;
}
