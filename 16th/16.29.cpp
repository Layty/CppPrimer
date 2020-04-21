

// 16.28 编写自己的shared_ptr  和 unique_ptr
// shared_ptr  保存一个指针,参数为value type*  按照delete是返回void的函数  using DelFuncPtr = void (*)(T*);
// unique_ptr 保存的是删除器的类,因为不会被改变

#include <vector>
#include <string>
#include <iostream>

//*********************************************************************************************************
/*
    0. 参考声明 template< class T > class shared_ptr;
    1. 内容指针,引用计数指针,删除器的函数指针
    2. 构造函数参考,先实现默认构造,即带一个指针和一个删除器
    3. 拷贝构造
    4. 拷贝赋值,这里需要释放原来的空间,可以使用 swap 传递值的方式 来实现
    5. 所以我们先实现swap   void swap( shared_ptr& r ) noexcept;
    6. 析构函数,判断引用,判断是否nullptr
    7. void reset( Y* ptr, Deleter d );
*/
template <typename T>
class SharedPtr
{
    using DelFuncPtr = void (*)(T *);

public:
    SharedPtr(T *ptr = nullptr, DelFuncPtr del = nullptr)
        : ptr_(ptr), count_ptr_(new size_t(ptr != nullptr)), del_(del)
    {
    }

    ~SharedPtr()
    {
        if (!ptr_)
            return;
        if (--*count_ptr_ == 0)
        {
            del_ ? del_(ptr_) : delete ptr_;
            delete count_ptr_;
        }
        ptr_ = nullptr;
        count_ptr_ = nullptr;
    }

    SharedPtr(const SharedPtr &sp) : ptr_(sp.ptr_), count_ptr_(sp.count_ptr_), del_(sp.del_)
    {
        ++*count_ptr_;
    }

    SharedPtr &operator=(SharedPtr sp)
    {
        swap(sp);
        return *this;
    }

    SharedPtr(const SharedPtr &&sp) noexcept : SharedPtr() { swap(sp); }

    void reset(T *ptr = nullptr, DelFuncPtr del = nullptr)
    {
        SharedPtr tmp(ptr, del);
        swap(tmp);
    }

    void swap(SharedPtr &r) noexcept
    {
        using std::swap;
        swap(ptr_, r.ptr_);
        swap(count_ptr_, r.count_ptr_);
        swap(del_, r.del_);
    }

    T *get() const noexcept { return ptr_; }
    T &operator*() const noexcept { return *get(); }
    T *operator->() const noexcept { return get(); }
    size_t use_count() const noexcept { return *count_ptr_; }
    explicit operator bool() const noexcept { return ptr_ != nullptr; }

private:
    T *ptr_ = nullptr;
    size_t *count_ptr_ = nullptr;
    DelFuncPtr del_ = nullptr;
};
// template <class T>
// class SharedPtr
// {
//     using DelFuncPtr = void (*)(T *);

// private:
//     T *ptr_ = nullptr;
//     size_t *count_ptr_ = nullptr;
//     DelFuncPtr del_ = nullptr;

// public:
//     SharedPtr(T *ptr = nullptr, DelFuncPtr del = nullptr) : ptr_(ptr), del_(del), count_ptr_(new size_t(ptr_ != nullptr)) {}
//     SharedPtr(const SharedPtr &s) : ptr_(s.ptr_), del_(s.del_), count_ptr_(s.count_ptr_)
//     {
//         ++*s.count_ptr_;
//     }
//     SharedPtr &operator=(SharedPtr s) //这里使用值传递,会先复制一份
//     {
//         //交换自己和临时的,临时的在退出的时候会自动调用析构释放
//         swap(s);
//         return *this;
//     }

//     void reset(T *ptr = nullptr, DelFuncPtr d = nullptr)
//     {
//         auto news = SharedPtr(ptr, d);
//         swap(news);
//     }

//     void swap(SharedPtr &r) noexcept
//     {
//         using std::swap;
//         swap(ptr_, r.ptr_);
//         swap(count_ptr_, r.count_ptr_);
//         swap(del_, r.del_);
//     }
//     ~SharedPtr()
//     {
//         if (ptr_ == nullptr)
//             return;
//         if (0 == --*count_ptr_)
//         {
//             del_ == nullptr ? delete (ptr_) : del_(ptr_);
//             delete count_ptr_;
//         }
//         ptr_ = nullptr;
//         count_ptr_ = nullptr;
//     }

//     T *get() const noexcept
//     {
//         return ptr_;
//     }

//     size_t use_count() const noexcept
//     {
//         return *count_ptr_;
//     }

//     T &operator*() const noexcept
//     {
//         return *ptr_;
//     }
//     T *operator->() const noexcept
//     {
//         return ptr_;
//     }
//     //检查 *this 是否存储非空指针，即是否有 get() != nullptr
//     explicit operator bool() const noexcept
//     {
//         return get() != nullptr;
//     }
// };

//*********************************************************************************************************
/**unique_ptr 保存的是删除器的类,因为不会被改变
 */

class Delete
{
public:
    template <typename T>
    void operator()(T *ptr) const { delete ptr; }
};

template <typename T, typename D = Delete>
class UniquePtr
{
private:
    T *ptr_ = nullptr;
    D del_;

public:
    UniquePtr(T *ptr = nullptr, const D &d = D()) : ptr_(ptr), del_(d) {}
    ~UniquePtr() { del_(ptr_); }
    UniquePtr(const UniquePtr &) = delete;
    UniquePtr &operator=(const UniquePtr &) = delete;

    UniquePtr(UniquePtr &&other) noexcept : ptr_(other.ptr_), del_(std::move(other.del_))
    {
        other.ptr_ = nullptr;
    }

    UniquePtr &operator=(UniquePtr &&other) noexcept
    {
        if (this != &other)
        {
            reset();
            ptr_ = other.ptr_;
            del_ = std::move(other.del_);
            other.ptr_ = nullptr;
        }
        return *this;
    }
    UniquePtr &operator=(std::nullptr_t) noexcept
    {
        reset();
        return *this;
    }
    T *release() noexcept
    {
        T *ret = ptr_;
        ptr_ = nullptr;
        return ret;
    }

    void reset(T *ptr = nullptr)
    {
        del_(ptr_);
        ptr_ = ptr;
    }

    void swap(UniquePtr &other) noexcept
    {
        using std::swap;
        swap(ptr_, other.ptr_);
        swap(del_, other.del_);
    }

    T *get() const noexcept
    {
        return ptr_;
    }

    D &get_deleter() noexcept { return del_; }
    const D &get_deleter() const noexcept { return del_; }

    T &operator*() const noexcept
    {
        return *ptr_;
    }
    T *operator->() const noexcept
    {
        return ptr_;
    }
    T &operator[](size_t i) const { return ptr_[i]; }
    //检查 *this 是否存储非空指针，即是否有 get() != nullptr
    explicit operator bool() const noexcept
    {
        return get() != nullptr;
    }
};
//*********************************************************************************************************
class DebugDelete
{
private:
    std::ostream &dbgos;

public:
    DebugDelete(std::ostream &o = std::cout) : dbgos(o) {}
    template <typename T>
    void operator()(T *elem) const
    {
        dbgos << "delete by DebugDelete" << std::endl;
        delete elem;
    }
};

// 16.24 为你的Blob添加一个构造函数支持两个迭代器

// 16.12 编写你自己的 Blob 和 BlobPtr 模版,包含书中未定义的多个const成员

#include <vector>
#include <memory>
#include <string>
#include <list>
#include <iostream>
#include <initializer_list>
#include <exception>
#include <algorithm>

#define shared_ptr SharedPtr

template <typename T>
class BlobPtr;
template <typename T>
class Blob;
template <typename T>
class ConstBlobPtr;

template <typename T>
bool operator==(const Blob<T> &a, const Blob<T> &b);
template <typename T>
bool operator!=(const Blob<T> &a, const Blob<T> &b);
template <typename T>
bool operator<(const Blob<T> &a, const Blob<T> &b);
template <typename T>
bool operator>(const Blob<T> &a, const Blob<T> &b);
template <typename T>
bool operator<=(const Blob<T> &a, const Blob<T> &b);
template <typename T>
bool operator>=(const Blob<T> &a, const Blob<T> &b);

template <typename T>
class Blob
{
    friend BlobPtr<T>;
    friend ConstBlobPtr<T>;

    friend bool operator==<T>(const Blob<T> &a, const Blob<T> &b);
    friend bool operator!=<T>(const Blob<T> &a, const Blob<T> &b);
    // clang-format off
    friend bool operator< <T>(const Blob<T> &a, const Blob<T> &b);
    friend bool operator> <T>(const Blob<T> &a, const Blob<T> &b);
    // clang-format on
    friend bool operator<=<T>(const Blob<T> &a, const Blob<T> &b);
    friend bool operator>=<T>(const Blob<T> &a, const Blob<T> &b);

    // 以下两个应该是为了外部方便获取类型
    typedef T value_type;
    typedef typename std::vector<T>::size_type size_type;

private:
    shared_ptr<std::vector<T>> data;
    void check(size_type i, const std::string &msg) const;

public:
    Blob() : data(new std::vector<T>()) {}
    // 16.24
    template <typename type_it>
    Blob(type_it a, type_it b) : data(new std::vector<T>(a, b)) {}

    Blob(const Blob<T> &s) : data(new std::vector<T>(*s.data)) {}
    Blob(Blob<T> &&a) noexcept : data(std::move(a.data)) {}

    Blob &operator=(const Blob<T> &s);
    Blob &operator=(Blob<T> &&) noexcept;

    Blob(std::initializer_list<T> il) : data(new std::vector<T>(il)) {}
    size_type size() const { return data->size(); }
    bool empty() const { return data->empty(); }

    void push_back(T &val) { data->push_back(val); };
    void push_back(const T &val) { data->push_back(std::move(val)); }
    void pop_back();

    T &back();
    const T &back() const;
    T &front();
    const T &front() const;

    T &operator[](size_type i);
    const T &operator[](size_type i) const;

    BlobPtr<T> begin();
    BlobPtr<T> end();

    ConstBlobPtr<T> cbegin() const;
    ConstBlobPtr<T> cend() const;

    void print(std::ostream &o);
};

template <typename T>
Blob<T> &Blob<T>::operator=(const Blob<T> &s)
{
    data = new std::vector<T>(*s.data);
    return *this;
}

template <typename T>
Blob<T> &Blob<T>::operator=(Blob<T> &&s) noexcept
{
    if (this != s)
    {
        data = std::move(s.data);
        s.data = nullptr;
    }
    return *this;
}

template <typename T>
void Blob<T>::print(std::ostream &o)
{
    for (auto ch : (*data))
        o << ch << ",";
    o << std::endl;
}

template <typename T>
void Blob<T>::check(size_type i, const std::string &msg) const
{
    if (i >= size())
    {
        throw std::out_of_range(msg);
    }
}

template <typename T>
void Blob<T>::pop_back()
{
    check(0, "empty to pop_back");
    data->pop_back();
}

template <typename T>
T &Blob<T>::back()
{
    check(0, "Get empty Back()");
    return data->back();
}
template <typename T>
const T &Blob<T>::back() const
{
    check(0, "Get empty Back()");
    return data->back();
}

template <typename T>
T &Blob<T>::front()
{
    check(0, "Get empty front()");
    return data->front();
}
template <typename T>
const T &Blob<T>::front() const
{
    check(0, "Get empty front()");
    return data->front();
}

template <typename T>
T &Blob<T>::operator[](size_type i)
{
    check(i, "Get [" + std::to_string(i) + "]");
    return data->at(i);
}

template <typename T>
const T &Blob<T>::operator[](size_type i) const
{
    check(i, "Get [" + std::to_string(i) + "]");
    return data->at(i);
}

template <typename T>
BlobPtr<T> Blob<T>::begin()
{
    return BlobPtr<T>(*this);
}
template <typename T>
BlobPtr<T> Blob<T>::end()
{
    return BlobPtr<T>(*this, size());
}

template <typename T>
ConstBlobPtr<T> Blob<T>::cbegin() const
{
    return ConstBlobPtr<T>(*this);
}
template <typename T>
ConstBlobPtr<T> Blob<T>::cend() const
{
    return ConstBlobPtr<T>(*this, size());
}

//****************************************************************************
template <typename T>
bool operator==(const Blob<T> &a, const Blob<T> &b)
{
    return (*a.data == *b.data);
}
template <typename T>
bool operator!=(const Blob<T> &a, const Blob<T> &b)
{
    return !(a == b);
}

template <typename T>
bool operator<(const Blob<T> &a, const Blob<T> &b)
{
    return std::lexicographical_compare(a.data->begin(), a.data->end(), b.data->begin(), b.data->end());
}

template <typename T>
bool operator>(const Blob<T> &a, const Blob<T> &b)
{
    return (b < a);
}
template <typename T>
bool operator<=(const Blob<T> &a, const Blob<T> &b)
{
    return !(b > a);
}
template <typename T>
bool operator>=(const Blob<T> &a, const Blob<T> &b)
{
    return !(a < b);
}

//****************************************************************************
// 定义 Blob::iterator

template <typename T>
bool operator==(const BlobPtr<T> &, const BlobPtr<T> &);
template <typename T>
bool operator!=(const BlobPtr<T> &, const BlobPtr<T> &);
template <typename T>
bool operator<(const BlobPtr<T> &, const BlobPtr<T> &);
template <typename T>
bool operator>(const BlobPtr<T> &, const BlobPtr<T> &);
template <typename T>
bool operator<=(const BlobPtr<T> &, const BlobPtr<T> &);
template <typename T>
bool operator>=(const BlobPtr<T> &, const BlobPtr<T> &);

template <typename T>
class BlobPtr
{
private:
    std::weak_ptr<std::vector<T>> wptr;
    std::size_t curr;
    shared_ptr<std::vector<T>> check(size_t i, const std::string &msg) const;

public:
    friend bool operator==<T>(const BlobPtr<T> &a, const BlobPtr<T> &b);
    friend bool operator!=<T>(const BlobPtr<T> &a, const BlobPtr<T> &b);
    // clang-format off
    friend bool operator< <T>(const BlobPtr<T> &a, const BlobPtr<T> &b);
    friend bool operator> <T>(const BlobPtr<T> &a, const BlobPtr<T> &b);
    friend bool operator<=<T>(const BlobPtr<T> &a, const BlobPtr<T> &b);
    friend bool operator>=<T>(const BlobPtr<T> &a, const BlobPtr<T> &b);
    // clang-format on

    BlobPtr() : curr(0) {}
    BlobPtr(const Blob<T> &pt, size_t at = 0) : wptr(pt.data), curr(at) {}
    T &operator*()
    {
        return check(curr, "Get elem[] out of range")->at(curr);
    }
    T &operator[](size_t at)
    {
        return check(at, "Get elem[] out of range")->at(at);
    }
    const T &operator*() const
    {
        return check(curr, "Get elem[] out of range")->at(curr);
    }
    const T &operator[](size_t at) const
    {
        return check(at, "Get elem[] out of range")->at(at);
    }
    const T *operator->() const
    {
        return &this->operator*();
    }
    T *operator->()
    {
        return &this->operator*();
    }
    BlobPtr operator++();
    BlobPtr operator++(int);
    BlobPtr operator--();
    BlobPtr operator--(int);
    BlobPtr &operator+=(size_t);
    BlobPtr &operator-=(size_t);
    BlobPtr operator+(size_t) const;
    BlobPtr operator-(size_t) const;
};

template <typename T>
shared_ptr<std::vector<T>> BlobPtr<T>::check(size_t i, const std::string &msg) const
{
    auto spt = wptr.lock();
    if (spt)
    { // 使用之前必须复制到 shared_ptr
        if (i >= spt->size())
            throw std::out_of_range(msg);
    }
    else
    {
        throw std::runtime_error("unbound Blob<T>Ptr");
    }
    return spt;
}

// 前置++,先++,再返回
template <typename T>
BlobPtr<T> BlobPtr<T>::operator++()
{
    check(curr, "++");
    curr++;
    return *this;
}
template <typename T>
BlobPtr<T> BlobPtr<T>::operator++(int)
{
    auto ret = *this;
    ++*this;
    return *this;
}
// 前置++,先++,再返回
template <typename T>
BlobPtr<T> BlobPtr<T>::operator--()
{
    check(curr, "--");
    curr--;
    return *this;
}
template <typename T>
BlobPtr<T> BlobPtr<T>::operator--(int)
{
    auto ret = *this;
    --*this;
    return *this;
}

template <typename T>
BlobPtr<T> &BlobPtr<T>::operator+=(size_t off)
{
    curr += off;
    check(curr, "increment past end of Blob<T>Ptr");
    return *this;
}
template <typename T>
BlobPtr<T> &BlobPtr<T>::operator-=(size_t off)
{
    curr -= off;
    check(curr, "increment past end of Blob<T>Ptr");
    return *this;
}

template <typename T>
BlobPtr<T> BlobPtr<T>::operator+(size_t off) const
{
    BlobPtr<T> ret = *this;
    ret += off;
    return ret;
}

template <typename T>
BlobPtr<T> BlobPtr<T>::operator-(size_t off) const
{
    BlobPtr<T> ret = *this;
    ret -= off;
    return ret;
}

//***********            friend           *******************************//
template <typename T>
bool operator==(const BlobPtr<T> &a, const BlobPtr<T> &b)
{
    return (a.curr == b.curr);
}
template <typename T>
bool operator!=(const BlobPtr<T> &a, const BlobPtr<T> &b)
{
    return !(a == b);
}

template <typename T>
bool operator<(const BlobPtr<T> &a, const BlobPtr<T> &b)
{
    return (a.curr < b.curr);
}
template <typename T>
bool operator>(const BlobPtr<T> &a, const BlobPtr<T> &b)
{
    return (b < a);
}
template <typename T>
bool operator<=(const BlobPtr<T> &a, const BlobPtr<T> &b)
{
    return !(a > b);
}
template <typename T>
bool operator>=(const BlobPtr<T> &a, const BlobPtr<T> &b)
{
    return !(a < b);
}

// template <typename T>
// std::ostream &operator<<(std::ostream &o, const T &Blob_val)
// {

// }

//****************************************************************************
// 定义 Blob::iterator

template <typename T>
bool operator==(const ConstBlobPtr<T> &, const ConstBlobPtr<T> &);
template <typename T>
bool operator!=(const ConstBlobPtr<T> &, const ConstBlobPtr<T> &);
template <typename T>
bool operator<(const ConstBlobPtr<T> &, const ConstBlobPtr<T> &);
template <typename T>
bool operator>(const ConstBlobPtr<T> &, const ConstBlobPtr<T> &);
template <typename T>
bool operator<=(const ConstBlobPtr<T> &, const ConstBlobPtr<T> &);
template <typename T>
bool operator>=(const ConstBlobPtr<T> &, const ConstBlobPtr<T> &);

template <typename T>
class ConstBlobPtr
{
private:
    std::weak_ptr<std::vector<T>> wptr;
    std::size_t curr;
    shared_ptr<std::vector<T>> check(size_t i, const std::string &msg) const;

public:
    friend bool operator==<T>(const ConstBlobPtr<T> &a, const ConstBlobPtr<T> &b);
    friend bool operator!=<T>(const ConstBlobPtr<T> &a, const ConstBlobPtr<T> &b);
    // clang-format off
    friend bool operator< <T>(const ConstBlobPtr<T> &a, const ConstBlobPtr<T> &b);
    friend bool operator> <T>(const ConstBlobPtr<T> &a, const ConstBlobPtr<T> &b);
    friend bool operator<=<T>(const ConstBlobPtr<T> &a, const ConstBlobPtr<T> &b);
    friend bool operator>=<T>(const ConstBlobPtr<T> &a, const ConstBlobPtr<T> &b);
    // clang-format on

    ConstBlobPtr() : curr(0) {}
    ConstBlobPtr(const Blob<T> &pt, size_t at = 0) : wptr(pt.data), curr(at) {}
    const T &operator*() const
    {
        return check(curr, "Get elem[] out of range")->at(curr);
    }
    const T &operator[](size_t at) const
    {
        return check(at, "Get elem[] out of range")->at(at);
    }
    const T *operator->() const
    {
        return &this->operator*();
    }
    ConstBlobPtr operator++();
    ConstBlobPtr operator++(int);
    ConstBlobPtr operator--();
    ConstBlobPtr operator--(int);
    ConstBlobPtr &operator+=(size_t);
    ConstBlobPtr &operator-=(size_t);
    ConstBlobPtr operator+(size_t) const;
    ConstBlobPtr operator-(size_t) const;
};

template <typename T>
shared_ptr<std::vector<T>> ConstBlobPtr<T>::check(size_t i, const std::string &msg) const
{
    auto spt = wptr.lock();
    if (spt)
    { // 使用之前必须复制到 shared_ptr
        if (i >= spt->size())
            throw std::out_of_range(msg);
    }
    else
    {
        throw std::runtime_error("unbound Blob<T>Ptr");
    }
    return spt;
}

// 前置++,先++,再返回
template <typename T>
ConstBlobPtr<T> ConstBlobPtr<T>::operator++()
{
    check(curr, "++");
    curr++;
    return *this;
}
template <typename T>
ConstBlobPtr<T> ConstBlobPtr<T>::operator++(int)
{
    auto ret = *this;
    ++*this;
    return *this;
}
// 前置++,先++,再返回
template <typename T>
ConstBlobPtr<T> ConstBlobPtr<T>::operator--()
{
    check(curr, "--");
    curr--;
    return *this;
}
template <typename T>
ConstBlobPtr<T> ConstBlobPtr<T>::operator--(int)
{
    auto ret = *this;
    --*this;
    return *this;
}

template <typename T>
ConstBlobPtr<T> &ConstBlobPtr<T>::operator+=(size_t off)
{
    curr += off;
    check(curr, "increment past end of Blob<T>Ptr");
    return *this;
}
template <typename T>
ConstBlobPtr<T> &ConstBlobPtr<T>::operator-=(size_t off)
{
    curr -= off;
    check(curr, "increment past end of Blob<T>Ptr");
    return *this;
}

template <typename T>
ConstBlobPtr<T> ConstBlobPtr<T>::operator+(size_t off) const
{
    ConstBlobPtr<T> ret = *this;
    ret += off;
    return ret;
}

template <typename T>
ConstBlobPtr<T> ConstBlobPtr<T>::operator-(size_t off) const
{
    ConstBlobPtr<T> ret = *this;
    ret -= off;
    return ret;
}

//***********            friend           *******************************//
template <typename T>
bool operator==(const ConstBlobPtr<T> &a, const ConstBlobPtr<T> &b)
{
    return (a.curr == b.curr);
}
template <typename T>
bool operator!=(const ConstBlobPtr<T> &a, const ConstBlobPtr<T> &b)
{
    return !(a == b);
}

template <typename T>
bool operator<(const ConstBlobPtr<T> &a, const ConstBlobPtr<T> &b)
{
    return (a.curr < b.curr);
}
template <typename T>
bool operator>(const ConstBlobPtr<T> &a, const ConstBlobPtr<T> &b)
{
    return (b < a);
}
template <typename T>
bool operator<=(const ConstBlobPtr<T> &a, const ConstBlobPtr<T> &b)
{
    return !(a > b);
}
template <typename T>
bool operator>=(const ConstBlobPtr<T> &a, const ConstBlobPtr<T> &b)
{
    return !(a < b);
}
//*******************************************
int main(int argc, char const *argv[])
{
    // try
    // {
    //     std::list<std::string> ls({"A1", "A2", "A3"});
    //     Blob<std::string> blob_s(ls.begin(), ls.end());
    //     blob_s.print(std::cout);
    // }
    // catch (const std::exception &e)
    // {
    //     std::cerr << e.what() << '\n';
    // }

    // try
    // {
    //     std::string hello = "hello";
    //     Blob<std::string> blob_s({"1"});
    //     blob_s.pop_back();
    //     // 触发check 异常
    //     //blob_s.pop_back();
    //     blob_s.push_back("2");
    //     blob_s.push_back(hello);
    //     //
    //     std::cout << blob_s.size() << std::endl;
    //     blob_s.print(std::cout);
    //     std::cout << blob_s.back() << std::endl;
    //     std::cout << blob_s[blob_s.size() - 1] << std::endl;

    //     // 测试 iterator
    //     BlobPtr<std::string> blob_pt1(blob_s);
    //     std::cout << blob_pt1[1] << std::endl;

    //     // 测试迭代器
    //     std::cout << "By iterator" << std::endl;
    //     for (auto b = blob_s.begin(); b != blob_s.end(); b++)
    //     {
    //         std::cout << *b << std::endl;
    //     }
    // }
    // catch (const std::exception &msg)
    // {
    //     std::cout << msg.what() << std::endl;
    // }

    // {
    //     Blob<std::string> sb1{"a", "b", "c"};
    //     Blob<std::string> sb2 = sb1;

    //     sb2[2] = "b";

    //     if (sb1 > sb2)
    //     {
    //         for (auto iter = sb2.cbegin(); iter != sb2.cend(); ++iter)
    //             std::cout << *iter << " ";
    //         std::cout << std::endl;
    //     }

    //     ConstBlobPtr<std::string> iter(sb2);
    //     std::cout << iter->size() << std::endl;
    // }
    Blob<std::string> sb1{"a", "b", "c"};
    Blob<std::string> sb2 = sb1;

    sb2[2] = "b";

    if (sb1 > sb2)
    {
        for (auto iter = sb2.cbegin(); iter != sb2.cend(); ++iter)
        {
            std::cout << *iter << " ";
        }
        std::cout << std::endl;
    }

    // ConstBlobPtr<std::string> iter(sb2);
    // std::cout << iter->size() << std::endl;

    // std::vector<std::string> vec{"good", "for", "you"};
    // Blob<std::string> sb3(vec.begin(), vec.end());

    // for (auto &&s : sb3)
    // {
    //     std::cout << s << " ";
    // }
    // std::cout << "\n";

    while (1)
        ;
    return 0;
}