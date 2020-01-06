/**
 * 编写一个函数，接受一对指向vector的迭代器和一个int值。在两个迭代器指定的范围中查找给定的值，返回一个布尔值来指出是否找到
 */

#include <iostream>
#include <vector>
using namespace std;

bool findInt(vector<int>::iterator src_begin, vector<int>::iterator src_end, int num)
{

    for (vector<int>::iterator i = src_begin; i != src_end; i++) {
        if (*i == num) return true;
    }
    return false;
}

int main(int argc, const char** argv)
{
    vector<int> a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};

    for (auto ch : a) {
        cout << ch << ",";
    }
    cout << endl;

    bool find = findInt(a.begin(), a.end(), 155);
    cout << "find 155 is " << boolalpha << find << endl;
    find = findInt(a.begin(), a.end(), 1);
    cout << "find 1 is " << boolalpha << find << endl;

    while (1) {
        ;
    }

    return 0;
}