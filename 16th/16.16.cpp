// 16.16 定义模版类的vec 替代之前的Strvec

#include <memory>
#include <algorithm>
#include <utility>
#include <initializer_list>
#include <exception>
#include <string>
#include <stdexcept>
#include <iostream>
// using std::cin;
// using std::cout;
// using std::endl;

// 定义一些公共操作
// 从一个迭代器范围复制 到指定的位置,返回内存的首地址和尾地址+1 也就是返回 begin和end

/**
 如何设计一个 vector
 1. 首先我们定义一个分配器,一个首地址,尾地址,以及容量
 2. 提供 size,begin,end,capacity,at,[]
 3. push_back
        chk_n_alloc();
        3.1 检查容量的操作
        3.2 容量的分配,这里需要设计一个移动函数    
        alloc.construct
        3.3 数据构造 
 4. 移动函数涉及
        alloc_n_move
        4.1 内存分配
        4.2 原来数据的移动
 5.设计reserve
        5.1 内存分配和移动 alloc_n_move
 6.设计resize
    重设容器大小以容纳 count 个元素。

    若当前大小大于 count ，则减小容器为其首 count 个元素。
    设置指针,调用元素的析构函数 destroy析构在已分配存储中的对象 

    若当前大小小于 count ，则后附额外元素，并以 value 的副本初始化。
    也就是调用reserve


*/

template <typename>
class Vec;

template <typename T>
bool operator==(const Vec<T> &, const Vec<T> &);
template <typename T>
bool operator!=(const Vec<T> &, const Vec<T> &);
template <typename T>
bool operator<(const Vec<T> &, const Vec<T> &);
template <typename T>
bool operator>(const Vec<T> &, const Vec<T> &);
template <typename T>
bool operator<=(const Vec<T> &, const Vec<T> &);
template <typename T>
bool operator>=(const Vec<T> &, const Vec<T> &);

template <typename T>
class Vec
{
    friend bool operator==<T>(const Vec<T> &, const Vec<T> &);
    friend bool operator!=<T>(const Vec<T> &, const Vec<T> &);
    // clang-format off
    friend bool operator< <T>(const Vec<T>&, const Vec<T>&);
    friend bool operator> <T>(const Vec<T>&, const Vec<T>&);
    // clang-format on
    friend bool operator<=<T>(const Vec<T> &, const Vec<T> &);
    friend bool operator>=<T>(const Vec<T> &, const Vec<T> &);

private:
    T *elements;
    T *first_free;
    T *cap;
    std::allocator<T> alloc;

    std::pair<T *, T *> alloc_n_copy(const T *b, const T *e);
    void range_initialize(const T *first, const T *last);
    void free();
    void reallocate();
    void alloc_n_move(size_t new_cap);
    void chk_n_alloc()
    {
        if (size() == capacity())
            reallocate();
    }

public:
    Vec(std::initializer_list<T>);
    Vec() : elements(nullptr), first_free(nullptr), cap(nullptr) {}
    Vec(const Vec<T> &);
    //------------------------------------------------------------Vec<T> &operator=(const Vec<T> &s);
    Vec &operator=(const Vec<T> &s);
    Vec(Vec<T> &&) noexcept;
    Vec &operator=(Vec<T> &&) noexcept;

    T *begin() const { return elements; }
    T *end() const { return first_free; }
    T &at(size_t pos) { return *(elements + pos); }
    const T &at(size_t pos) const { return *(elements + pos); }

    T &operator[](size_t n) { return elements[n]; }
    const T &operator[](size_t n) const { return elements[n]; }

    void push_back(const T &);
    size_t size() const { return first_free - elements; }
    size_t capacity() const { return cap - elements; }

    void reserve(size_t new_cap);
    void resize(size_t count);
    void resize(size_t count, const T &);

    ~Vec();
};

template <typename T>
std::pair<T *, T *> Vec<T>::alloc_n_copy(const T *b, const T *e)
{
    auto data = alloc.allocate(e - b);
    return {data, std::uninitialized_copy(b, e, data)};
}

template <typename T>
void Vec<T>::range_initialize(const T *first, const T *last)
{
    auto newdata = alloc_n_copy(first, last);
    elements = newdata.first;
    first_free = cap = newdata.second;
}
template <typename T>
void Vec<T>::free()
{
    if (elements)
    {
        //执行元素的析构函数
        for_each(elements, first_free, [this](T &rhs) { alloc.destroy(&rhs); });
        //释放vector内存
        alloc.deallocate(elements, cap - elements);
    }
}

template <typename T>
Vec<T>::Vec(std::initializer_list<T> il)
{
    range_initialize(il.begin(), il.end());
}
template <typename T>
Vec<T>::Vec(const Vec<T> &s)
{
    range_initialize(s.begin, s.end);
}

template <typename T>
Vec<T> &Vec<T>::operator=(const Vec<T> &s)
{
    if (this != s)
    {
        auto data = alloc_n_copy(s.begin(), s.end());
        free();
        elements = data.first;
        first_free = cap = data.second;
    }
    return *this;
}
template <typename T>
Vec<T>::Vec(Vec<T> &&s) noexcept
{
    elements = s.elements;
    first_free = s.first_free;
    cap = s.cap;
    s.elements = s.first_free = s.cap = nullptr;
}
template <typename T>
Vec<T> &Vec<T>::operator=(Vec<T> &&s) noexcept
{
    if (this != &s)
    {
        free();
        elements = s.elements;
        first_free = s.first_free;
        cap = s.cap;
        s.elements = s.first_free = s.cap = nullptr;
    }
    return *this;
}

template <typename T>
Vec<T>::~Vec()
{
    free();
}

template <typename T>
void Vec<T>::alloc_n_move(size_t new_cap)
{
    auto newdata = alloc.allocate(new_cap);
    auto dest = newdata;
    auto elem = elements;
    for (size_t i = 0; i != size(); ++i)
        alloc.construct(dest++, std::move(*elem++));
    free();
    elements = newdata;
    first_free = dest;
    cap = elements + new_cap;
}
template <typename T>
void Vec<T>::reallocate()
{
    auto newcapacity = size() ? 2 * size() : 1;
    alloc_n_move(newcapacity);
}
template <typename T>
void Vec<T>::reserve(size_t new_cap)
{
    if (new_cap <= capacity())
        return;
    alloc_n_move(new_cap);
}

// resize
// 重设容器大小以容纳 count 个元素。
// 若当前大小大于 count ，则减小容器为其首 count 个元素。
// 若当前大小小于 count ，则后附额外元素，并以 value 的副本初始化。
template <typename T>
void Vec<T>::resize(size_t count, const T &s)
{
    if (count > size())
    {
        if (count > capacity())
            reserve(count * 2);
        for (size_t i = size(); i != count; ++i)
            alloc.construct(first_free++, s);
    }
    else if (count < size())
    {
        while (first_free != elements + count)
            alloc.destroy(--first_free);
    }
}

template <typename T>
void Vec<T>::resize(size_t count)
{
    resize(count, T());
}

template <typename T>
void Vec<T>::push_back(const T &s)
{
    chk_n_alloc();
    alloc.construct(first_free++, s);
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
template <typename T>
bool operator==(const Vec<T> &lhs, const Vec<T> &rhs)
{
    return (lhs.size() == rhs.size() &&
            std::equal(lhs.begin(), lhs.end(), rhs.begin()));
}

template <typename T>
bool operator!=(const Vec<T> &lhs, const Vec<T> &rhs)
{
    return !(lhs == rhs);
}

template <typename T>
bool operator<(const Vec<T> &lhs, const Vec<T> &rhs)
{
    return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(),
                                        rhs.end());
}

template <typename T>
bool operator>(const Vec<T> &lhs, const Vec<T> &rhs)
{
    return rhs < lhs;
}

template <typename T>
bool operator<=(const Vec<T> &lhs, const Vec<T> &rhs)
{
    return !(rhs < lhs);
}

template <typename T>
bool operator>=(const Vec<T> &lhs, const Vec<T> &rhs)
{
    return !(lhs < rhs);
}
int main()
{
    Vec<std::string> vec;
    vec.reserve(6);
    std::cout << "capacity(reserve to 6): " << vec.capacity() << std::endl;

    vec.reserve(4);
    std::cout << "capacity(reserve to 4): " << vec.capacity() << std::endl;

    vec.push_back("hello");
    vec.push_back("world");

    vec.resize(4);

    for (auto i = vec.begin(); i != vec.end(); ++i)
        std::cout << *i << std::endl;
    std::cout << "-EOF-" << std::endl;

    vec.resize(1);

    for (auto i = vec.begin(); i != vec.end(); ++i)
        std::cout << *i << std::endl;
    std::cout << "-EOF-" << std::endl;

    Vec<std::string> vec_list{"hello", "world", "pezy"};

    for (auto i = vec_list.begin(); i != vec_list.end(); ++i)
        std::cout << *i << " ";
    std::cout << std::endl;

    // Test operator==

    const Vec<std::string> const_vec_list{"hello", "world", "pezy"};
    if (vec_list == const_vec_list)
        for (const auto &str : const_vec_list)
            std::cout << str << " ";
    std::cout << std::endl;

    // Test operator<
    const Vec<std::string> const_vec_list_small{"hello", "pezy", "ok"};
    std::cout << (const_vec_list_small < const_vec_list) << std::endl;

    // Test []
    std::cout << const_vec_list_small[1] << std::endl;
    while (1)
        ;
}