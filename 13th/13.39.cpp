/*
    使用 allocator 实现自己的 vector<string>
13.39
    resize	重设容器大小以容纳 count 个元素。若当前大小大于 count ，则减小容器为其首 count 个元素。
    reserve 增加 vector 的容量到大于或等于 new_cap 的值 若 new_cap 大于当前的 capacity() ，则分配新存储，否则该方法不做任何事。reserve() 不更改 vector 的 size 
13.40
    增加一个 initiallizer_list 的构造函数
13.43
    重写 free ,使用foreach 和 lambda 取代 for 和destroy     
*/

#include <string>
#include <memory>
#include <utility>
#include <iostream>
#include <initializer_list>
#include <algorithm>
using std::cin;
using std::cout;
using std::endl;
using std::initializer_list;
using std::pair;
using std::string;

class StrVec
{
private:
    string *elements;   //首元素
    string *first_free; //最后一个元素之后的元素,也就是end
    string *cap;        //实际容量之后的一个元素

public:
    StrVec() : elements(nullptr), first_free(nullptr), cap(nullptr) {}
    StrVec(const StrVec &);
    StrVec(initializer_list<string> li);
    StrVec &operator=(const StrVec &);
    ~StrVec();

    void push_back(const string &);
    size_t size() const { return first_free - elements; }
    size_t capacity() const { return cap - elements; }
    string *begin() const { return elements; }
    string *end() const { return first_free; }
    void reserve(size_t new_cap);
    void resize(size_t count);
    void resize(size_t count, const std::string &);

private:
    std::allocator<string> alloc;
    void reallocate();
    void chk_n_alloc()
    {
        if (size() == capacity())
            reallocate();
    }
    void free();
    pair<string *, string *> allc_n_copy(const string *, const string *); // 从迭代器拷贝,返回首指针和尾指针
};

void StrVec::push_back(const string &s)
{
    chk_n_alloc();
    alloc.construct(first_free++, s); // 先复制,再++
}

pair<string *, string *> StrVec::allc_n_copy(const string *b, const string *e)
{
    auto data = alloc.allocate(e - b);
    return {data, std::uninitialized_copy(b, e, data)}; //指向最后复制的元素后一元素的迭代器
}

void StrVec::free()
{
    if (elements)
    {
        // for (auto i = first_free; i != elements;)
        // {
        //     alloc.destroy(--i); //先--到有效内存
        // }
        // 捕获了this,这里的alloc就是 this->alloc
        for_each(elements, first_free, [this](std::string &rhs) { alloc.destroy(&rhs); });
        alloc.deallocate(elements, cap - elements);
    }
}

StrVec::StrVec(const StrVec &s)
{
    auto data = allc_n_copy(s.begin(), s.end());
    elements = data.first;
    first_free = cap = data.second;
}

StrVec::StrVec(initializer_list<string> li)
{
    auto newdata = allc_n_copy(li.begin(), li.end());
    elements = newdata.first;
    first_free = cap = newdata.second;
}
StrVec::~StrVec()
{
    free();
}
StrVec &StrVec::operator=(const StrVec &s)
{
    auto data = allc_n_copy(s.begin(), s.end());
    free();
    elements = data.first;
    first_free = cap = data.second;
    return *this;
}

void StrVec::reallocate()
{
    auto newcap = size() ? 2 * size() : 1;
    auto data = alloc.allocate(newcap);
    auto dst = data;
    auto elm = elements;
    for (size_t i = 0; i != size(); ++i)
    {
        alloc.construct(dst++, std::move(*elm++)); // 从老空间拷贝
    }
    free(); //释放老元素,这里的elements 没有改变
    elements = data;
    first_free = dst;
    cap = elements + newcap; //起始地址加容量
}
//reserve 增加 vector 的容量到大于或等于 new_cap 的值 若 new_cap 大于当前的 capacity() ，
//则分配新存储，否则该方法不做任何事。reserve() 不更改 vector 的 size
void StrVec::reserve(size_t new_cap)
{
    if (new_cap > capacity())
    {
        auto data = alloc.allocate(new_cap);
        auto dst = data;
        auto elm = elements;
        for (size_t i = 0; i != size(); ++i)
        {
            alloc.construct(dst++, std::move(*elm++)); // 从老空间拷贝
        }
        free(); //释放老元素,这里的elements 没有改变
        elements = data;
        first_free = dst;
        cap = elements + new_cap; //起始地址加容量
    }
}
/*
resize重设容器大小以容纳 count 个元素。若当前大小大于 count ，则减小容器为其首 count 个元素。
*/
void StrVec::resize(size_t count, const std::string &s)
{
    int old_size = size();
    if (size() > count)
    {
        for (auto i = first_free; size() != count;)
        {
            alloc.destroy(--i); //先--到有效内存,会调用存储对象的析构函数
            first_free--;
        }
    }
    else if (size() < count)
    {
        //初始化构造
        reserve(count);
        for (; size() != count;)
            push_back(s);
    }
}

void StrVec::resize(size_t count)
{
    resize(count, string());
}

int main(int argc, char const *argv[])
{
    StrVec s = {"A", "B"};
    s.push_back("1");
    s.push_back("2");
    s.resize(5, "****");
    s.resize(4);

    StrVec s2(s);
    StrVec s3;
    s3.push_back("3");
    s3 = s2;

    StrVec vv[3] = {s, s2, s3};
    int j = 0;
    for (auto sv : vv)
    {
        cout << "[ " << j++ << " ]"
             << ": ";
        for (auto i = sv.begin(); i != sv.end(); i++)
        {
            cout << *i << " ";
        }
        cout << endl;
    }

    while (1)
        ;
    return 0;
}
