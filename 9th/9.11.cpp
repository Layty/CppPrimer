/*
对6种创建和初始化vector对象的方法，每一种都给出一个实例。解释每个vector包含什么值
*/

#include <iostream>
#include <vector>
using namespace std;

void printVecInfo(const vector<int> src)
{
    cout << "size=" << src.size() << "   :    ";
    for (auto ch : src) cout << ch << ",";
    cout << endl;
}

int main(int argc, const char** argv)
{
    using C = vector<int>;

    C a1;
    C a2{1, 2, 3, 4, 5, 6, 7, 8, 9};
    C a3 = a2;
    C a4(a2.begin(), a2.begin() + 2);
    C a5(5);
    C a6(6, 1);

    printVecInfo(a1); // size=0   :
    printVecInfo(a2); // size=9   :    1,2,3,4,5,6,7,8,9,
    printVecInfo(a3); // size=9   :    1,2,3,4,5,6,7,8,9,
    printVecInfo(a4); // size=2   :    1,2,
    printVecInfo(a5); // size=5   :    0,0,0,0,0,
    printVecInfo(a6); // size=6   :    1,1,1,1,1,1,

    while (1) {
        ;
    }

    return 0;
}