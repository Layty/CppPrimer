/**
 *重写上一题的函数，返回一个迭代器指向找到的元素。注意，程序必须处理未找到给定值的情况
 */

#include <iostream>
#include <vector>
using namespace std;

vector<int>::iterator findInt(vector<int>::iterator src_begin, vector<int>::iterator src_end, int num)
{

    for (vector<int>::iterator i = src_begin; i != src_end; i++) {
        if (*i == num) return i;
    }
    return src_end;
}

int main(int argc, const char** argv)
{
    vector<int> a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};

    for (auto ch : a) {
        cout << ch << ",";
    }
    cout << endl;

    auto find = findInt(a.begin(), a.end(), 155);
    if (find == a.end()) {
        cout << "no number find" << endl;
    }
    find = findInt(a.begin(), a.end(), 1);
    if (find != a.end()) {
        cout << "find 1 is " << *find << endl;
    }
    while (1) {
        ;
    }

    return 0;
}