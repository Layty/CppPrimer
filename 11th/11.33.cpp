#include "../include/include.h"
#include <fstream>
#include <sstream>

map<string, string> build_map(ifstream &if_map)
{
    map<string, string> m;
    string key, value;
    while (if_map >> key && getline(if_map, value))
    {
        // remove 只是移动元素 ,没有删除,返回的是最后的符合的迭代器
        auto it = remove_if(value.begin(), value.end(), [](const char ch) { return (ch == ' '); });
        value.erase(it, value.end());

        if (value.size() == 0)
            cout << "size=0" << endl;
        else
        {
            m[key] = value;
        }
    };

    return m;
}

string transform(const map<string, string> &m, const string &txt)
{
    auto it = m.find(txt);
    if (it != m.end())
        return it->second;
    else
        return txt;
}

void word_transform(ifstream &map, ifstream &input)
{
    auto string_map = build_map(map);
    string txt_line;
    while (getline(input, txt_line))
    {
        istringstream words(txt_line);
        string ch;
        while (words >> ch)
        {
            cout << transform(string_map, ch) << " ";
        }
        cout << endl;
    }
}

int main(int argc, char const *argv[])
{
    ifstream if_rules("E:\\rules.txt");
    ifstream if_txt("E:\\me.txt");
    if (if_rules && if_txt)
    {
        word_transform(if_rules, if_txt);
    }
    else
    {
        if (!if_rules)
            cout << " open rules " << endl;
        if (!if_txt)
            cout << " open txt " << endl;
    }
    while (1)
        ;
}
