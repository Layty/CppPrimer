/*
编写函数，返回一个动态分配的int的vector。将此vector传递给另一个函数。这个函数读取标准输入，
将读入的值保存在vector中。再将vector传递给另一个函数，打印读入的值。记得在恰当的时刻delete vector
*/
#include <vector>
#include <memory>
#include <iostream>

using namespace std;

vector<int> *get_vector_int_pt(void)
{
    return new vector<int>();
}

vector<int> *put_vector_int_pt(vector<int> *pt)
{
    int num;
    while (cin >> num)
        pt->push_back(num);

    return pt;
}

void show_vector_int_pt(vector<int> *pt)
{
    for (int a : *pt)
        cout << a << " ";
    cout << endl;
}

int main(int argc, char const *argv[])
{
    vector<int> *t = get_vector_int_pt();
    put_vector_int_pt(t);
    show_vector_int_pt(t);
    delete t;

    while (1)
        ;
    return 0;
}
