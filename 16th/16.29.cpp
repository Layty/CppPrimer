// 修改你的Blob类,用你的shared_ptr 替代标准库的版本
// 这里不能使用weak_ptr了,应该自己再做一个,
// 在赋值迭代器的时候,weak_ptr 的赋值操作没有对 我们自己实现的 重载
// 这里我们修改Blob 不使用迭代器了
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

template <class T>
class SharedPtr
{
    using DelFuncPtr = void (*)(T *);

private:
    T *ptr_ = nullptr;
    size_t *count_ptr_ = nullptr;
    DelFuncPtr del_ = nullptr;

public:
    SharedPtr(T *ptr = nullptr, DelFuncPtr del = nullptr) : ptr_(ptr), del_(del), count_ptr_(new size_t(ptr_ != nullptr)) {}
    SharedPtr(const SharedPtr &s) : ptr_(s.ptr_), del_(s.del_), count_ptr_(s.count_ptr_)
    {
        ++*s.count_ptr_;
    }
    SharedPtr &operator=(SharedPtr s) //这里使用值传递,会先复制一份
    {
        //交换自己和临时的,临时的在退出的时候会自动调用析构释放
        swap(s);
        return *this;
    }

    void reset(T *ptr = nullptr, DelFuncPtr d = nullptr)
    {
        auto news = SharedPtr(ptr, d);
        swap(news);
    }

    void swap(SharedPtr &r) noexcept
    {
        using std::swap;
        swap(ptr_, r.ptr_);
        swap(count_ptr_, r.count_ptr_);
        swap(del_, r.del_);
    }
    ~SharedPtr()
    {
        if (ptr_ == nullptr)
            return;
        if (0 == --*count_ptr_)
        {
            del_ == nullptr ? delete (ptr_) : del_(ptr_);
            delete count_ptr_;
        }
        ptr_ = nullptr;
        count_ptr_ = nullptr;
    }

    T *get() const noexcept
    {
        return ptr_;
    }

    size_t use_count() const noexcept
    {
        return *count_ptr_;
    }

    T &operator*() const noexcept
    {
        return *ptr_;
    }
    T *operator->() const noexcept
    {
        return ptr_;
    }
    //检查 *this 是否存储非空指针，即是否有 get() != nullptr
    explicit operator bool() const noexcept
    {
        return get() != nullptr;
    }
};

template <typename T>
class Blob;

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
    SharedPtr<std::vector<T>> data;
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

int main(int argc, const char **argv)
{
    Blob<std::string> blob_s({"1", "2"});
    blob_s.print(std::cout);
    while (1)
        ;
    return 0;
}