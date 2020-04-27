// 15.13 给定下面的类，解释每个 print 函数的机理：在上述代码中存在问题吗？如果有，你该如何修改它？
#include <iostream>
#include <string>
using namespace std;
class base
{
public:
    string name() { return basename; }
    virtual void print(ostream &os) { os << basename; }

private:
    string basename;
};

class derived : public base
{
public:
    //void print(ostream &os) { print(os); os << " " << i; }
    void print(ostream &os)
    {
        //this->base::print(os);
        base::print(os);
        os << " " << i;
    }

private:
    int i;
};

int main(int argc, char const *argv[])
{
    derived A;
    A.print(std::cout);
    while (1)
        ;
    return 0;
}
