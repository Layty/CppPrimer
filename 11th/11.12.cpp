/*写程序，读入string和int序列，将每个string和int序列存入一个pair中，pair保存在一个vector中*/
/*至少有三种创建pair的方法*/

#include "../include/include.h"
int main(int argc, char const *argv[])
{
    vector<pair<string, int>> v;

    string s;
    int i;

    while (cin >> s >> i)
    {
        //v.push_back(make_pair(s, i));
        //v.push_back({s, i});
        v.push_back(pair<string, int>(s, i));
    }

    for (auto ch : v)
    {
        cout << ch.first << "--" << ch.second << endl;
    }
    while (1)
    {
        /* code */
    }

    return 0;
}
