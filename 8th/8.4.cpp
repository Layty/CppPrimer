/*
8.4 编写函数，以读模式打开一个文件，将其内容读入到一个string的vector中，将每一行作为一个独立的元素存于vector中
8.5 按照单词分割
*/

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

void Each(istream &in, string option)
{
    if (!in)
    {
        cerr << "Check FIle" << endl;
        while (1)
            ;
    }
    string s;
    vector<string> v;

    if (option == "line")
    {
        while (getline(in, s))
            v.push_back(s);
    }
    else
    {
        while (in >> s)
            v.push_back(s);
    }

    for (auto a : v)
    {
        cout << a << endl;
    }
}

int main(int argc, char const *argv[])
{
    string filepath = "C:\\JLink.log";
    ifstream in(filepath);

    cout << "Split By Line" << endl;
    Each(in, "line");
    in.close();

    cout << "Split By Word" << endl;
    in.open(filepath);
    Each(in, "word");

    while (1)
        ;
    return 0;
}
