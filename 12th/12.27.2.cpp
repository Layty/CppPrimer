#include <string>
#include <map>
#include <set>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <memory>

using namespace std;

/*
    定义一个类 保存 string,行号,以及一个指向txt的指针
*/
class ResultQuery
{
    friend ostream &print(ostream &, const ResultQuery &);

public:
    // 单词
    string w;
    // 行号的列表
    shared_ptr<set<int>> lines;
    // 全部的文本,可以通过行号寻找
    shared_ptr<vector<string>> txtline;

public:
    ResultQuery(string word, shared_ptr<set<int>> line_num, shared_ptr<vector<string>> txt) : w(word), lines(line_num), txtline(txt){};
    ~ResultQuery(){};
};

class TextQuery
{
private:
    /* data */
    shared_ptr<vector<string>> txtline;
    // 因为在ret里面共享的是set的行号,所以这里也是行号共享指针,而不是整个map
    map<string, shared_ptr<set<int>>> data;

public:
    TextQuery(ifstream &file);
    ResultQuery Query(string &w);
    ~TextQuery(){};
};

TextQuery::TextQuery(ifstream &file) : txtline(new vector<string>)
{
    // 读入文件到文件流,保存每一行到vector<string>
    string s;
    int line_at = 0;
    while (getline(file, s))
    {
        txtline->push_back(s);
        string ch;
        istringstream ss(s);
        while (ss >> ch)
        {
            if (!data[ch])
                data[ch].reset(new set<int>);
            data[ch]->insert(line_at);
        }
        line_at++;
    }
}

ResultQuery TextQuery::Query(string &w)
{
    static shared_ptr<std::set<int>> nodate(new std::set<int>);
    auto found = data.find(w);
    if (found == data.end())
        return ResultQuery(w, nodate, txtline);
    else
        return ResultQuery(w, data[w], txtline);
}
//ostream &print(ostream &, const ResultQuery &)
ostream &print(ostream &out, const ResultQuery &want)
{
    out << "----------------------------------------------" << endl;
    out << "string:" << want.w << endl;
    out << "Txt List:" << endl;
    //if (want.lines) // 先要判断指针是否存在
    {
        for (auto ls : *(want.lines))
            out << ls << ":\t\t\t" << want.txtline->at(ls) << endl;
        //qr.input->at(i)
    }

    out << "----------------------------------------------" << endl;
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
        print(cout, tq.Query(s)) << endl;
    }
}

int main(int argc, char const *argv[])
{
    ifstream fs("D:\\a.txt");
    if (fs)
        runQueries(fs);
    else
        cout << "fs open failed " << endl;

    while (1)
        ;
    return 0;
}
