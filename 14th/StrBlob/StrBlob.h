#ifndef __STR_BLOB_H__
#define __STR_BLOB_H__

#include <vector>
#include <memory>
#include <iostream>
#include <initializer_list>
#include <exception>

using std::cout;
using std::endl;
using std::initializer_list;
using std::make_shared;
using std::ostream;
using std::shared_ptr;
using std::string;
using std::vector;

class StrBlobPtr;
class ConstStrBlobPtr;
/**
 * @brief vector<string>
 * 
 */
class StrBlob
{
    using size_type = vector<string>::size_type;
    friend std::ostream &operator<<(std::ostream &o, const StrBlob &s);
    friend bool operator==(const StrBlob &, const StrBlob &);
    friend bool operator!=(const StrBlob &, const StrBlob &);
    friend bool operator<(const StrBlob &, const StrBlob &);
    friend bool operator>(const StrBlob &, const StrBlob &);
    friend bool operator<=(const StrBlob &, const StrBlob &);
    friend bool operator>=(const StrBlob &, const StrBlob &);

    friend class StrBlobPtr;
    friend class ConstStrBlobPtr;

private:
    shared_ptr<vector<string>>
        data;
    void check(size_type at, const string err_message) const;

public:
    StrBlob() : data(make_shared<vector<string>>()) {}
    StrBlob(initializer_list<string> il) : data(make_shared<vector<string>>(il)) {}
    // 拷贝构造,拷贝赋值,移动构造,移动赋值
    StrBlob(const StrBlob &s) : data(make_shared<vector<string>>(*s.data)) {}
    StrBlob &operator=(const StrBlob &s);
    StrBlob(StrBlob &&s) noexcept : data(std::move(s.data)) {}
    StrBlob &operator=(StrBlob &&s);

    void push_back(const string &s) { data->push_back(s); }
    void push_back(string &&s) { data->push_back(std::move(s)); }
    void pop_back();
    string &front();
    string &back();
    const string &front() const;
    const string &back() const;
    string &operator[](size_t at);
    const string &operator[](size_t at) const;

    // 迭代器相关的
    StrBlobPtr begin();       // { return StrBlobPtr(*this); }
    StrBlobPtr end();         //{ return StrBlobPtr(*this, data->size()); }
    ConstStrBlobPtr cbegin(); // { return StrBlobPtr(*this); }
    ConstStrBlobPtr cend();   //{ return StrBlobPtr(*this, data->size()); }

    size_type size() const { return data->size(); }
};

inline StrBlob &StrBlob::operator=(const StrBlob &s)
{
    data = make_shared<vector<string>>(*s.data);
    return *this;
}

inline StrBlob &StrBlob::operator=(StrBlob &&s)
{
    if (this != &s)
    {
        data = s.data;
        s.data = nullptr;
    }
    return *this;
}

inline void StrBlob::check(size_type at, const string err_message) const
{
    if (at >= data->size())
        throw std::out_of_range(err_message);
}

inline void StrBlob::pop_back()
{
    check(0, "try to pop empty vector!!!");
    data->pop_back();
}

inline string &StrBlob::front()
{
    check(0, "try to get front empty vector!!!");
    return data->front();
}

inline string &StrBlob::back()
{
    check(0, "try to get back empty vector!!!");
    return data->back();
}
inline const string &StrBlob::front() const
{
    check(0, "try to get front empty vector!!!");
    return data->front();
}

inline const string &StrBlob::back() const
{
    check(0, "try to get back empty vector!!!");
    return data->back();
}

inline string &StrBlob::operator[](size_t at)
{
    check(at, "out of range!!!");
    return data->at(at);
}
inline const string &StrBlob::operator[](size_t at) const
{
    check(at, "out of range!!!");
    return data->at(at);
}

/**
 * @brief vector<string> iterator
 * 
 */
class StrBlobPtr
{
    friend bool operator==(const StrBlobPtr &, const StrBlobPtr &);
    friend bool operator!=(const StrBlobPtr &, const StrBlobPtr &);
    friend bool operator<(const StrBlobPtr &, const StrBlobPtr &);
    friend bool operator>(const StrBlobPtr &, const StrBlobPtr &);
    friend bool operator<=(const StrBlobPtr &, const StrBlobPtr &);
    friend bool operator>=(const StrBlobPtr &, const StrBlobPtr &);

private:
    std::weak_ptr<vector<string>> wptr;
    // convert weak_ptr to shared_ptr
    shared_ptr<vector<string>> check(size_t at, string err_msg) const;
    size_t curr;

public:
    StrBlobPtr() : curr(0) {}
    StrBlobPtr(StrBlob &s, size_t at = 0) : wptr(s.data), curr(at) {}

    StrBlobPtr &operator++();
    StrBlobPtr &operator--();
    // 后置版本返回的是原来的值的拷贝,再++,所以不能返回引用
    StrBlobPtr operator++(int);
    StrBlobPtr operator--(int);
    StrBlobPtr &operator+=(int);
    StrBlobPtr &operator-=(int);
    StrBlobPtr operator+(int) const;
    StrBlobPtr operator-(int) const;
    string &operator[](size_t);
    const string &operator[](size_t) const;
    string &operator*();
    const string &operator*() const;

    // 迭代器指向string 那么 *it 是string 而 it-> 自然是string的操作了
    string *operator->();
    const string *operator->() const;
};
inline shared_ptr<vector<string>> StrBlobPtr::check(size_t at, string err_msg) const
{
    auto ret = wptr.lock();
    if (!ret)
        throw std::runtime_error("No shared_ptr get!!!");
    if (at > ret->size()) //because of at==ret->size when iterator arrive the end
        throw std::out_of_range("out of range to check StrBlobPtr of" + err_msg);
    return ret;
}
inline StrBlobPtr &StrBlobPtr::operator++()
{
    ++curr;
    check(curr, "err to ++ ");
    return *this;
}
inline StrBlobPtr &StrBlobPtr::operator--()
{
    --curr;
    check(curr, "err to -- ");
    return *this;
}
inline StrBlobPtr StrBlobPtr::operator++(int)
{
    StrBlobPtr ret = *this;
    ++*this;
    return ret;
}
inline StrBlobPtr StrBlobPtr::operator--(int)
{
    StrBlobPtr ret = *this;
    --*this;
    return ret;
}
inline StrBlobPtr &StrBlobPtr::operator+=(int offset)
{
    curr += offset;
    check(curr, "err to += ");
    return *this;
}
inline StrBlobPtr &StrBlobPtr::operator-=(int offset)
{
    curr -= offset;
    check(curr, "err to -= ");
    return *this;
}

inline StrBlobPtr StrBlobPtr::operator+(int offset) const
{
    StrBlobPtr ret = *this;
    ret += offset;
    return *this;
}
inline StrBlobPtr StrBlobPtr::operator-(int offset) const
{
    StrBlobPtr ret = *this;
    ret -= offset;
    return *this;
}
inline string &StrBlobPtr::operator[](size_t offset)
{
    auto ret = check(offset, "Get [] err");
    return (*ret)[offset];
}
inline const string &StrBlobPtr::operator[](size_t offset) const
{
    auto ret = check(offset, "Get [] err");
    return (*ret)[offset];
}

inline string &StrBlobPtr::operator*()
{
    //auto ret = check(curr, "Get [] err");
    //return ret->at(curr);
    return (*this)[curr];
}
inline const string &StrBlobPtr::operator*() const
{
    return (*this)[curr];
}

// 迭代器指向string 那么 *it 是string 而 it-> 自然是string的操作了
inline string *StrBlobPtr::operator->()
{
    return &(this->operator*());
}
inline const string *StrBlobPtr::operator->() const
{
    return &(this->operator*());
}

// 个人觉得应该是 非const的迭代器继承自const的迭代器 const_iterator
// --这里的const 是指不能通过该迭代器修改指向的内容
/**
 * @brief vector<string> iterator
 * 
 */
class ConstStrBlobPtr
{
    friend bool operator==(const ConstStrBlobPtr &, const ConstStrBlobPtr &);
    friend bool operator!=(const ConstStrBlobPtr &, const ConstStrBlobPtr &);
    friend bool operator<(const ConstStrBlobPtr &, const ConstStrBlobPtr &);
    friend bool operator>(const ConstStrBlobPtr &, const ConstStrBlobPtr &);
    friend bool operator<=(const ConstStrBlobPtr &, const ConstStrBlobPtr &);
    friend bool operator>=(const ConstStrBlobPtr &, const ConstStrBlobPtr &);

private:
    std::weak_ptr<vector<string>> wptr;
    // convert weak_ptr to shared_ptr
    shared_ptr<vector<string>> check(size_t at, string err_msg) const;
    size_t curr;

public:
    ConstStrBlobPtr() : curr(0) {}
    ConstStrBlobPtr(const StrBlob &s, size_t at = 0) : wptr(s.data), curr(at) {}

    ConstStrBlobPtr &operator++();
    ConstStrBlobPtr &operator--();
    // 后置版本返回的是原来的值的拷贝,再++,所以不能返回引用
    ConstStrBlobPtr operator++(int);
    ConstStrBlobPtr operator--(int);
    ConstStrBlobPtr &operator+=(int);
    ConstStrBlobPtr &operator-=(int);
    ConstStrBlobPtr operator+(int) const;
    ConstStrBlobPtr operator-(int) const;
    //string &operator[](size_t); --这里的const 是指不能通过该迭代器修改指向的内容
    const string &operator[](size_t) const;
    //string &operator*();
    const string &operator*() const;
    //string *operator->();  --这里的const 是指不能通过该迭代器修改指向的内容
    const string *operator->() const;
};
inline shared_ptr<vector<string>> ConstStrBlobPtr::check(size_t at, string err_msg) const
{
    auto ret = wptr.lock();
    if (!ret)
        throw std::runtime_error("No shared_ptr get!!!");
    if (at > ret->size()) //because of at==ret->size when iterator arrive the end
        throw std::out_of_range("out of range to check ConstStrBlobPtr of" + err_msg);
    return ret;
}
inline ConstStrBlobPtr &ConstStrBlobPtr::operator++()
{
    ++curr;
    check(curr, "err to ++ ");
    return *this;
}
inline ConstStrBlobPtr &ConstStrBlobPtr::operator--()
{
    --curr;
    check(curr, "err to -- ");
    return *this;
}
inline ConstStrBlobPtr ConstStrBlobPtr::operator++(int)
{
    ConstStrBlobPtr ret = *this;
    ++*this;
    return ret;
}
inline ConstStrBlobPtr ConstStrBlobPtr::operator--(int)
{
    ConstStrBlobPtr ret = *this;
    --*this;
    return ret;
}
inline ConstStrBlobPtr &ConstStrBlobPtr::operator+=(int offset)
{
    curr += offset;
    check(curr, "err to += ");
    return *this;
}
inline ConstStrBlobPtr &ConstStrBlobPtr::operator-=(int offset)
{
    curr -= offset;
    check(curr, "err to -= ");
    return *this;
}

inline ConstStrBlobPtr ConstStrBlobPtr::operator+(int offset) const
{
    ConstStrBlobPtr ret = *this;
    ret += offset;
    return *this;
}
inline ConstStrBlobPtr ConstStrBlobPtr::operator-(int offset) const
{
    ConstStrBlobPtr ret = *this;
    ret -= offset;
    return *this;
}
// inline string &ConstStrBlobPtr::operator[](size_t offset)
// {
//     auto ret = check(offset, "Get [] err");
//     return (*ret)[offset];
// }
inline const string &ConstStrBlobPtr::operator[](size_t offset) const
{
    auto ret = check(offset, "Get [] err");
    return (*ret)[offset];
}

// inline string &ConstStrBlobPtr::operator*()
// {
//     //auto ret = check(curr, "Get [] err");
//     //return ret->at(curr);
//     return (*this)[curr];
// }
inline const string &ConstStrBlobPtr::operator*() const
{
    return (*this)[curr];
}

// 迭代器指向string 那么 *it 是string 而 it-> 自然是string的操作了
inline const string *ConstStrBlobPtr::operator->() const
{
    return &(this->operator*());
}

#endif // !__STR_BLOB_H__
