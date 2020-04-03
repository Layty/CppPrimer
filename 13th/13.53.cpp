/*
13.30 增加swap
13.22 使有指针的类表现为值
13.53 增加移动构造 和移动赋值
13.54  同上

*/
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

class HasPtr
{
private:
    string *ps;
    int i;

public:
    friend void swap(HasPtr &a, HasPtr &b);
    friend bool operator<(const HasPtr &lhs, const HasPtr &rhs);
    HasPtr(const string &s = string()) : ps(new string(s)), i(0) {}

    HasPtr(const HasPtr &s) : ps(new string(*(s.ps))), i(s.i)
    {
        std::cout << "call copy construct" << std::endl;
    }

    // add move
    HasPtr(HasPtr &&p) noexcept : ps(p.ps), i(p.i)
    {
        std::cout << "call move construct" << std::endl;
        p.ps = 0;
    }
    // HasPtr &operator=(HasPtr s)
    // {
    //     cout << "operator=" << endl;
    //     this->swap(s);
    //     return *this;
    // }
    HasPtr &operator=(HasPtr &s)
    {
        auto newp = new std::string(*s.ps);
        delete ps;
        ps = newp;
        i = s.i;
        std::cout << "call copy assignment" << std::endl;
        return *this;
    }
    HasPtr &operator=(HasPtr &&p) noexcept
    {
        std::cout << "call move assignment" << std::endl;
        if (&p == this)
            return *this;
        ps = p.ps;
        i = p.i;
        p.ps = 0;
        return *this;
    }

    void swap(HasPtr &s)
    {
        using std::swap;
        swap(ps, s.ps);
        swap(i, s.i);
        cout << "-------swap -----" << *s.ps << "<<>><<>>" << *ps << endl;
    }
    ~HasPtr() { delete ps; }

    ostream &print(ostream &c)
    {
        c << "string= " << *ps << endl;
        c << "i= " << i << endl;
        return c;
    }
};

void swap(HasPtr &a, HasPtr &b)
{
    cout << "-------swap -----" << *a.ps << "<<>><<>>" << *b.ps << endl;

    swap(a.i, b.i);
    swap(a.ps, b.ps);
}

// HasPtr &operator=(HasPtr &s)
// {
//     swap(*this, s);
// }

// // HasPtr &operator=(HasPtr &&p) noexcept
// // {
// // }

bool operator<(const HasPtr &lhs, const HasPtr &rhs)
{
    return *lhs.ps < *rhs.ps;
}

int main(int argc, char const *argv[])
{
    HasPtr A("7");
    HasPtr B("3");
    HasPtr C("9");

    B = A;
    B = std::move(C);

    // vector<HasPtr> vs;
    // vs.push_back(A);
    // vs.push_back(B);
    // vs.push_back(C);
    // vs.push_back(HasPtr("1"));
    // for (auto i : vs)
    //     i.print(cout);
    // sort(vs.begin(), vs.end());
    // for (auto i : vs)
    //     i.print(cout);

    while (1)
        ;
    return 0;
}
