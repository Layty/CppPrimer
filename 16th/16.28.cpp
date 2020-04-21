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

int main(int argc, const char **argv)
{
    {
        using std::string;
        using std::vector;
        DebugDelete d;

        string *mystring = new string("123456");

        //SharedPtr<string> myshared_string(mystring, [](string *p) {std::cout << "Call delete from lambda...\n";delete p; });
        SharedPtr<string> myshared_string(mystring, [](string *p) { DebugDelete()(p); });
        std::cout << *myshared_string.get() << std::endl;

        std::cout << "Test Copy assiment" << std::endl;
        SharedPtr<string> myshared_string3(new string("55555"));
        myshared_string3 = myshared_string;

        std::cout << "Test Copy Construct" << std::endl;
        SharedPtr<string> myshared_string2(myshared_string);
        std::cout << myshared_string.use_count() << std::endl;
    }

    {
        using std::string;
        using std::vector;
        std::cout << "Test Unique Ptr" << std::endl;
        UniquePtr<string> s1(new string("A10086"));
        std::cout << *s1.get() << std::endl;

        UniquePtr<string, DebugDelete> s2(new string("B10086"), DebugDelete());
        std::cout << *s1.get() << std::endl;
    }
    while (1)
        ;
    return 0;
}