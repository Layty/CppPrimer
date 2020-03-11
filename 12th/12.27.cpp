#include <string>
#include <map>
#include <set>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <memory>

using namespace std;

// 0. 没有使用 Query类保存结果,这里的简单例子直接从 TextQuery取得结果
// 1. 使用 vector<string> 保存每行文字
// 2. 每个string 有一个set 保存行号
// 3. 使用 map<string,set>绑定这个数据

class TextQuery
{
private:
    /* data */
    vector<string> txtline;
    map<string, set<int>> data;

public:
    TextQuery(ifstream &file);
    ~TextQuery(){};
    ostream &GetWant(ostream &out, string ch);
};

TextQuery::TextQuery(ifstream &file)
{
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
            data[ch].insert(line_at);
        }
        line_at++;
    }
}

ostream &TextQuery::GetWant(ostream &out, string ch)
{
    out << "[" << ch << "]:" << endl;
    for (auto i = data[ch].begin(); i != data[ch].end(); i++)
        out << "Line[" << (*i) + 1 << "]: " << txtline[*i] << endl;
    return out;
}

void runQueries(ifstream &file)
{
    // 从文件流建立查询的数据
    TextQuery tq(file);
    while (true)
    {
        cout << "Enter what you want to find?" << endl;
        string s;
        if (!(cin >> s) || s == "q")
            break;
        tq.GetWant(cout, s);
    }
}

int main(int argc, char const *argv[])
{
    ifstream fs("D:\\a.txt");
    runQueries(fs);
    return 0;
}
