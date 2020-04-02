/*
13.27 使有指针的类表现为指针
*/

#include <iostream>
#include <string>
using namespace std;

class HasPtr
{
private:
    string *ps;
    int i;
    size_t *use;

public:
    HasPtr(const string &s = string()) : ps(new string(s)), i(0), use(new size_t(1)) {}

    //HasPtr(const HasPtr &s) : ps(new string(*(s.ps))), i(s.i) {}
    // 拷贝构造,
    HasPtr(const HasPtr &s) : use(s.use), ps(s.ps), i(s.i)
    {
        ++*use;
    }

    HasPtr &operator=(HasPtr &s)
    {
        ++*s.use;
        if (--*use == 0)
        {
            delete ps;
            delete use;
        }
        ps = s.ps;
        use = s.use;
        i = s.i;

        return *this;
    }
    //~HasPtr() { delete ps; }
    ~HasPtr()
    {
        if (--*use == 0)
        {
            delete ps;
            delete use;
        }
    }

    ostream &print(ostream &c)
    {
        c << "string= " << *ps << endl;
        c << "i= " << i << endl;
        return c;
    }
};

int main(int argc, char const *argv[])
{
    {
        // HasPtr A("123");
        // HasPtr B("456");
        // A.print(cout);
        // B.print(cout);
        // B = A;
        // B.print(cout);
        // HasPtr C(A);
        // C.print(cout);

        HasPtr A1("333");
        HasPtr A3("444");
        HasPtr A2(A1);

        A1.print(cout);
        A2.print(cout);
        A2 = A3;
        A2.print(cout);
    }

    while (1)
        ;
    return 0;
}