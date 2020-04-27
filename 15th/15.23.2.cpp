// 自己写一个 重载基类的函数名

#include <iostream>
#include <string>
using namespace std;
class base
{
public:
    void p() { cout << "base" << endl; }
    void p(int i) { cout << "base int" << endl; }
};

class dev1 : public base
{
public:
    using base::p; // 关键是这一句
    void p(int i) { cout << "dev1 int" << endl; }
};

int main(int argc, char const *argv[])
{
    dev1 d1;
    d1.p();        // base
    d1.p(1);       // d1
    d1.base::p(1); //base
    while (1)
        ;
    return 0;
}
