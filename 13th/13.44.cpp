/**
 * 实现自己的string
 * 
 */

#include <memory>
#include <utility>
#include <algorithm>
#include <iostream>

class String
{
private:
    char *elem;
    char *end;
    std::allocator<char> alloc;

    std::pair<char *, char *> alloc_n_copy(const char *, const char *);
    void range_initializer(const char *, const char *);
    void free();
    /* data */
public:
    friend std::ostream &operator<<(std::ostream &o, String &s);
    String() : elem(nullptr), end(nullptr) {}
    String(const char *);
    String(const String &);
    ~String();
    String &operator=(const String &);
};

std::pair<char *, char *> String::alloc_n_copy(const char *b, const char *e)
{
    auto str = alloc.allocate(e - b);
    return std::make_pair(str, std::uninitialized_copy(b, e, str));
}
void String::range_initializer(const char *b, const char *e)
{
    auto ret = alloc_n_copy(b, e);
    elem = ret.first;
    end = ret.second;
}

String::String(const char *s)
{
    char *sl = const_cast<char *>(s);
    while (*sl)
        ++sl;
    range_initializer(s, ++sl);
}
String::String(const String &s)
{
    std::cout << "copy-construct" << std::endl;
    range_initializer(s.elem, s.end);
}
void String::free()
{
    //std::cout << "free" << std::endl;
    if (elem)
    {
        //std::cout << "free elem" << std::endl;
        std::for_each(elem, end, [this](char &s) { alloc.destroy(&s); });
        alloc.deallocate(elem, end - elem);
    }
}

String::~String()
{
    free();
}

String &String::operator=(const String &s)
{

    // auto newstr = alloc_n_copy(rhs.elem, rhs.end);
    // free();
    // elem = newstr.first;
    // end = newstr.second;
    // std::cout << "copy-assignment" << std::endl;
    // return *this;

    if (&s == this)
    {
        std::cout << "copy-assignment self!!!!!!" << std::endl;
        return *this;
    }

    range_initializer(s.elem, s.end);
    std::cout << "copy-assignment" << std::endl;
    return *this;
}

std::ostream &operator<<(std::ostream &o, String &s)
{
    return o << s.elem;
}

int main(int argc, char const *argv[])
{
    {
        /*常规构造*/
        String sa("abcdefg");
        std::cout << sa << std::endl;

        /*自赋值*/
        sa = sa;
        String *p = &sa;
        sa = *p;
        std::cout << sa << std::endl;

        /*拷贝构造*/
        String sb = sa;
        std::cout << sb << std::endl;

        /*拷贝赋值*/
        String sc;
        sc = sa;
        std::cout << sc << std::endl;
    }

    while (1)
        ;
    return 0;
}
