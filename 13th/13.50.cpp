/**
 * 13.49 为String 定义 移动构造和移动赋值
 * 
 * 13.48  定义一个vector<String> 查看push_back复制了几次
 * 
 * 13.44实现自己的string
 * 
 */

#include <memory>
#include <utility>
#include <algorithm>
#include <iostream>
#include <vector>

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
    String(String &&) noexcept;
    ~String();
    String &operator=(const String &);
    String &operator=(String &&s) noexcept;
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

String::String(String &&s) noexcept
{
    std::cout << "move-construct" << std::endl;

    elem = s.elem;
    end = s.end;
    alloc = s.alloc;
    s.elem = s.end = nullptr;
}

String &String::operator=(String &&s) noexcept
{
    std::cout << "move operator =" << std::endl;

    if (this == &s)
        return *this;

    elem = s.elem;
    end = s.end;
    alloc = s.alloc;
    s.elem = s.end = nullptr;
    return *this;
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
    if (1)
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

        /*移动构造*/
        String sd(std::move(sa));
        std::cout << sd << std::endl;
        /*移动赋值*/
        sb = String("new move operator string");
        std::cout << sb << std::endl;
    }

    // {
    //     std::vector<String> vs;
    //     //vs.reserve(100);        //-------------------------------加上这句话就只有一次拷贝
    //     String a("123");
    //     std::cout << __LINE__ << std::endl;
    //     vs.push_back(a);
    //     std::cout << __LINE__ << std::endl;
    //     vs.push_back(a);
    //     std::cout << __LINE__ << std::endl;
    //     vs.push_back(a);
    //     std::cout << __LINE__ << std::endl;

    //     String b("123");
    //     vs.push_back(b);
    //     std::cout << __LINE__ << std::endl;
    //     vs.push_back(b);
    //     std::cout << __LINE__ << std::endl;
    // }

    // // 127
    // // copy-construct
    // // 129
    // // copy-construct
    // // copy-construct
    // // 131
    // // copy-construct
    // // copy-construct
    // // copy-construct
    // // 133
    // // copy-construct
    // // 137
    // // copy-construct
    // // copy-construct
    // // copy-construct
    // // copy-construct
    // // copy-construct
    // // 139

    std::cout << __LINE__ << std::endl;
    std::vector<String> vs;
    vs.reserve(100);
    String a("a");
    String b("b");
    std::cout << __LINE__ << std::endl;
    vs.push_back(a);
    std::cout << __LINE__ << std::endl;
    vs.push_back(std::move(b));
    std::cout << __LINE__ << std::endl;
    vs.push_back(String("move"));

    while (1)
        ;
    return 0;
}
