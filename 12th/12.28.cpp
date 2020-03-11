/*
12.28：编写程序实现文本查询，不要定义类来管理数据，你的程序应该接受一个文件，并与用户交互来查询单词。
使用vector、map和set容器来保存来自文件的数据并生成查询结果。
*/

#include <string>
#include <map>
#include <set>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <memory>
using namespace std;

void test(ifstream &file)
{
    vector<string> txtline;
    map<string, set<int>> num;

    // 读入文件到文件流,保存每一行到vector<string>
    string s;
    int line_at = 0;
    while (getline(file, s))
    {
        txtline.push_back(s);
        string ch;
        istringstream ss(s);
        while (ss >> ch)
        {
            num[ch].insert(line_at);
        }
        line_at++;
    }

    string ch;
    cout << "pls input word to search" << endl;
    while (cin >> ch)
    {
        cout << "find " << ch << endl;
        for (auto i : num[ch])
        {
            cout << "line:" << i << "]:" << txtline[i] << endl;
        }
    }
}

int main(int argc, char const *argv[])
{
    ifstream fin("C:\\JLink.log");
    if (fin)
        test(fin);
    else
        cout << "check file" << endl;
    while (1)
        ;
    return 0;
}
