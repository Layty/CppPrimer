// 16.12 编写你自己的 Blob 和 BlobPtr 模版,包含书中未定义的多个const成员

#include <vector>
#include <memory>
#include <string>
#include <iostream>
#include <initializer_list>
#include <exception>
#include <algorithm>

template <typename T>
class BlobPtr;
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
    friend BlobPtr<T>;

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
    std::shared_ptr<std::vector<T>> data;
    void check(size_type i, const std::string &msg) const;

public:
    Blob() : data(std::make_shared<std::vector<T>>()) {}

    Blob(const Blob<T> &s) : data(std::make_shared<std::vector<T>>(*s.data)) {}
    Blob(Blob<T> &&a) noexcept : data(std::move(a.data)) {}

    Blob &operator=(const Blob<T> &s);
    Blob &operator=(Blob<T> &&) noexcept;

    Blob(std::initializer_list<T> il) : data(std::make_shared<std::vector<T>>(il)) {}
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

    void print(std::ostream &o);
};

template <typename T>
Blob<T> &Blob<T>::operator=(const Blob<T> &s)
{
    data = std::make_shared<std::vector<T>>(*s.data);
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

//****************************************************************************
template <typename T>
bool operator==(const Blob<T> &a, const Blob<T> &b)
{
    return (*a.data == *b.data);
}
template <typename T>
operator!=(const Blob<T> &a, const Blob<T> &b)
{
    return !(a == b);
}

template <typename T>
operator<(const Blob<T> &a, const Blob<T> &b)
{
    return std::lexicographical_compare(a.data->begin(), a.data->end(), b.data->begin(), b.data->end());
}

template <typename T>
operator>(const Blob<T> &a, const Blob<T> &b)
{
    return (b < a);
}
template <typename T>
operator<=(const Blob<T> &a, const Blob<T> &b)
{
    return !(b > a);
}
template <typename T>
operator>=(const Blob<T> &a, const Blob<T> &b)
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
    std::shared_ptr<std::vector<T>> check(size_t i, const std::string &msg);

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
std::shared_ptr<std::vector<T>> BlobPtr<T>::check(size_t i, const std::string &msg)
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

int main(int argc, char const *argv[])
{
    try
    {
        std::string hello = "hello";
        Blob<std::string> blob_s({"1"});
        blob_s.pop_back();
        // 触发check 异常
        //blob_s.pop_back();
        blob_s.push_back("2");
        blob_s.push_back(hello);
        //
        std::cout << blob_s.size() << std::endl;
        blob_s.print(std::cout);
        std::cout << blob_s.back() << std::endl;
        std::cout << blob_s[blob_s.size() - 1] << std::endl;

        // 测试 iterator
        BlobPtr<std::string> blob_pt1(blob_s);
        std::cout << blob_pt1[1] << std::endl;

        // 测试迭代器
        std::cout << "By iterator" << std::endl;
        for (auto b = blob_s.begin(); b != blob_s.end(); b++)
        {
            std::cout << *b << std::endl;
        }
    }
    catch (const std::exception &msg)
    {
        std::cout << msg.what() << std::endl;
    }

    while (1)
        ;
    return 0;
}
