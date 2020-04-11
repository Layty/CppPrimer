#include "StrBlob.h"
//****************************************************************************
std::ostream &operator<<(std::ostream &o, const StrBlob &s)
{
    for (size_t i = 0; i != s.size(); i++)
        o << s[i] << ",";
    return o;
}
bool operator==(const StrBlob &a, const StrBlob &b)
{
    return *a.data == *b.data;
}
bool operator!=(const StrBlob &a, const StrBlob &b)
{
    return !(a == b);
}
bool operator<(const StrBlob &a, const StrBlob &b)
{
    return std::lexicographical_compare(a.data->begin(), a.data->end(),
                                        b.data->begin(), b.data->end());
}
bool operator>(const StrBlob &a, const StrBlob &b)
{
    return b < a;
}
bool operator<=(const StrBlob &a, const StrBlob &b)
{
    return !(a > b);
}
bool operator>=(const StrBlob &a, const StrBlob &b)
{
    return !(a < b);
}

StrBlobPtr StrBlob::begin()
{
    return StrBlobPtr(*this);
}
StrBlobPtr StrBlob::end()
{
    return StrBlobPtr(*this, data->size());
}
ConstStrBlobPtr StrBlob::cbegin()
{
    return ConstStrBlobPtr(*this);
}
ConstStrBlobPtr StrBlob::cend()
{
    return ConstStrBlobPtr(*this, data->size());
}
//****************************************************************************
bool operator==(const StrBlobPtr &a, const StrBlobPtr &b)
{
    return a.curr == b.curr;
}
bool operator!=(const StrBlobPtr &a, const StrBlobPtr &b)
{
    return !(a == b);
}
bool operator<(const StrBlobPtr &a, const StrBlobPtr &b)
{
    return (a.curr < b.curr);
}
bool operator>(const StrBlobPtr &a, const StrBlobPtr &b)
{
    return (b < a);
}
bool operator<=(const StrBlobPtr &a, const StrBlobPtr &b)
{
    return (b > a);
}
bool operator>=(const StrBlobPtr &a, const StrBlobPtr &b)
{
    return (a < b);
}
//****************************************************************************
bool operator==(const ConstStrBlobPtr &a, const ConstStrBlobPtr &b)
{
    return a.curr == b.curr;
}
bool operator!=(const ConstStrBlobPtr &a, const ConstStrBlobPtr &b)
{
    return !(a == b);
}
bool operator<(const ConstStrBlobPtr &a, const ConstStrBlobPtr &b)
{
    return (a.curr < b.curr);
}
bool operator>(const ConstStrBlobPtr &a, const ConstStrBlobPtr &b)
{
    return (b < a);
}
bool operator<=(const ConstStrBlobPtr &a, const ConstStrBlobPtr &b)
{
    return (b > a);
}
bool operator>=(const ConstStrBlobPtr &a, const ConstStrBlobPtr &b)
{
    return (a < b);
}
//****************************************************************************

int main(int argc, char const *argv[])
{
    try
    {

        StrBlob ls({"A", "B", "C"});
        ls.push_back("D");
        ls.pop_back();
        std::cout << ls.front() << std::endl;
        std::cout << ls.back() << std::endl;
        std::cout << ls << std::endl;

        StrBlob ls2({"A", "B", "C"});
        std::cout << std::boolalpha << (ls == ls2) << std::endl;
        ls2.push_back("D");
        std::cout << std::boolalpha << (ls <= ls2) << std::endl;
        //
        ls.push_back("E");
        std::cout << ls << std::endl;
        std::cout << ls2 << std::endl;
        std::cout << std::boolalpha << (ls2 > ls) << std::endl;

        std::cout << "-------------------------------------" << std::endl;
        std::cout << "-------------Test iterator-----------" << std::endl;
        std::cout << "-------------------------------------" << std::endl;

        for (auto i = ls.begin(); i != ls.end(); i++)
        {
            std::cout << *i << ",";
            std::cout << std::endl
                      << "size= " << i->size() << std::endl;
            *i = "(" + *i + ")";
        }

        for (auto i = ls.begin(); i != ls.end(); i++)
        {
            std::cout << *i << ",";
            std::cout << std::endl
                      << "size= " << i->size() << std::endl;
        }

        for (auto i = ls.cbegin(); i != ls.cend(); i++)
        {
            std::cout << *i << ",";
            std::cout << std::endl
                      << "size= " << i->size() << std::endl;
            //*i = "(" + *i + ")"; // does not match any in class
            // inline string &ConstStrBlobPtr::operator[](size_t offset)
            // 只有 const string
        }

        /* code */
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    while (1)
        ;
    return 0;
}
