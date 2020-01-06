// 编写程序，判定两个vector是否相等。
#include <iostream>
#include <vector>
using namespace std;

int main(int argc, const char** argv)
{

    vector<int> a = {1, 2, 3, 4, 5, 6};
    vector<int> b = {2, 2, 3, 4, 5, 6};

    cout << boolalpha << (a == b) << endl;
    while (1)
        ;
}