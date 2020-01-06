/*如何用一个list<int>初始化一个vector<double>, 从一个vector<int>又该如何创建*/

#include <iostream>
#include <list>
#include <vector>
using namespace std;

int main(int argc, const char** argv)
{

    list<int> a = {1, 2, 3, 4, 5, 6, 7};
    vector<double> b(a.begin(), a.end());
    vector<int> c = {1, 2, 3, 4, 5, 6, 7};
    vector<double> d(c.begin(), c.end());

    return 0;
}
