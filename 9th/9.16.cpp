/*重写上一题的程序，比较一个list中的一个元素和一个vector中的元素。*/

#include <iostream>
#include <list>
#include <vector>
using namespace std;

int main(int argc, const char** argv)
{

    list<int> a(5, 1);
    vector<int> b(6, 1);

    cout << boolalpha << (vector<int>(a.begin(), a.end()) == b) << endl;
    while (1)
        ;
    return 0;
}