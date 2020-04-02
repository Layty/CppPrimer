/*
13.22 使有指针的类表现为值
*/

#include <iostream>
#include <string>
using namespace std;

class HasPtr
{
private:
    string *ps;
    int i;

public:
    HasPtr(const string &s = string()) : ps(new string(s)), i(0) {}

    HasPtr(const HasPtr &s) : ps(new string(*(s.ps))), i(s.i) {}

    HasPtr &operator=(const HasPtr &s)
    {
        auto newps = new string(*(s.ps));
        delete ps;
        ps = newps;
        i = s.i;
        return *this;
    }
    ~HasPtr() { delete ps; }

    ostream &print(ostream &c)
    {
        c << "string= " << *ps << endl;
        c << "i= " << i << endl;
        return c;
    }
};

int main(int argc, char const *argv[])
{
    HasPtr A("123");
    HasPtr B("456");
    A.print(cout);
    B.print(cout);
    B = A;
    B.print(cout);
    HasPtr C(A);
    C.print(cout);

    while (1)
        ;
    return 0;
}
