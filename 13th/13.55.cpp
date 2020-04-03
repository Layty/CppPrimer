/*

12.19 
12.20 读入文件 使用这个类
13.55  增加右值引用版本的 push_back



一个 StrBlob类,底层数据是指向 vector<string> 的指针
一个 StrBlob_ptr类,可以认为是StrBlob类的指针类

定义  StrBlob类,数据成员是 vector<string> 的shared_ptr
        begin  指向第一个元素的 StrBlob_ptr 也就是cur=0?
        end                   最后一个元素的指针cur=size()   end是开区间,所以不用减1
定义  StrBlob_ptr 类,指向 StrBlob类中的数据成员 *shared_ptr
        一个指向 vector<string> 的指针,带有小标
        *      获得string
        ++     将下标++


*/

#include <vector>
#include <string>
#include <memory>
#include <initializer_list>
#include <exception>
#include <iostream>
#include <fstream>

using namespace std;

class StrBlob_ptr;

class StrBlob
{
    using Blob_size_type = vector<string>::size_type;

    friend class StrBlob_ptr;

private:
    /* data */
    shared_ptr<vector<string>> data;

public:
    StrBlob() : data(make_shared<vector<string>>()) {}
    StrBlob(initializer_list<string> li) : data(make_shared<vector<string>>(li)) {}
    // 拷贝构造函数
    StrBlob(const StrBlob &src) : data(make_shared<vector<string>>(*src.data)) {}
    //拷贝赋值
    StrBlob &operator=(const StrBlob &src)
    {
        auto newptr = make_shared<vector<string>>(*src.data);
        data = newptr;
        return *this;
    }

    StrBlob_ptr begin(); //{ return StrBlob_ptr(*this); }
    StrBlob_ptr end();   //{ return StrBlob_ptr(*this, data->size()); }

    Blob_size_type size() const
    {
        return data->size();
    }

    bool empty() const
    {
        return data->empty();
    }

    bool check(Blob_size_type has, const string &msg) const
    {
        if (has >= data->size())
            throw std::out_of_range(msg);
    }

    void push_back(string &s)
    {
        data->push_back(s);
    }

    void push_back(string &&s)
    {
        std::cout << "psh_back:&&" << std::endl;
        data->push_back(std::move(s));
    }

    void pop_back()
    {
        check(0, "pop_back");
        data->pop_back();
    }

    string &front()
    {
        check(0, "front");
        return data->front();
    }

    string &back()
    {
        check(0, "back");
        return data->back();
    }

    const string &front() const
    {
        check(0, "front");
        return data->front();
    }

    const string &back() const
    {
        check(0, "back");
        return data->back();
    }

    ~StrBlob() {}
};

class StrBlob_ptr
{
private:
    // 底层指针指向的内容是 shared_ptr,可能存在释放的情况
    weak_ptr<vector<string>> ptr;
    int cur;
    shared_ptr<vector<string>> check(int size, const string msg) const;

public:
    // 构造函数,指向空的ptr
    StrBlob_ptr() : cur(0) {}
    StrBlob_ptr(StrBlob &s, int offset = 0) : ptr(s.data), cur(offset) {}
    ~StrBlob_ptr() {}

    // * 解引用
    string &deref() const;
    StrBlob_ptr &increase_ref();
    // 同时需要定义!= 这里应该还要判断 p的指向是否相同
    bool operator!=(const StrBlob_ptr &p) { return p.cur != cur; }
};

shared_ptr<vector<string>> StrBlob_ptr::check(int size, const string msg) const
{
    auto ptr_get = ptr.lock();
    if (!ptr_get)
        throw runtime_error(msg);
    if (size >= ptr_get->size())
        throw out_of_range(msg);
    return ptr_get;
}

string &StrBlob_ptr::deref() const
{
    auto ptr_get = check(cur, "get shared_ptr");
    return (*ptr_get)[cur];
}

StrBlob_ptr &StrBlob_ptr::increase_ref()
{
    check(cur, "get shared_ptr");
    cur++;
    return *this;
}

/*
 *   这两个函数一定要放到 StrBlob_ptr 这个类下面定义,因为用到了StrBlob_ptr具体的构造函数; 即使最开始已经声明了
 *    
 *
 *
*/
StrBlob_ptr StrBlob::begin()
{
    return StrBlob_ptr(*this);
}
StrBlob_ptr StrBlob::end()
{
    return StrBlob_ptr(*this, data->size());
}

int main(int argc, const char **argv)
{

    StrBlob csb{"1", "2", "3"};
    StrBlob sb{"A1", "A2", "A3"};

    csb.push_back("111");

    // StrBlob newCopy(csb);
    // std::cout << newCopy.front() << " " << newCopy.back() << std::endl;

    // newCopy = sb;
    // std::cout << newCopy.front() << " " << newCopy.back() << std::endl;

    // std::cout << csb.front() << " " << csb.back() << std::endl;
    // sb.back() = "change";
    // std::cout << sb.front() << " " << sb.back() << std::endl;

    // cout << "vector string :" << endl;
    // for (StrBlob_ptr ch = sb.begin(); ch != sb.end(); ch.increase_ref())
    //     cout << ch.deref() << ",";
    // cout << endl;

    // ifstream ifile("./12.19.cpp");
    // StrBlob fs_blob;
    // for (string str; getline(ifile, str);)
    //     fs_blob.push_back(str);

    // cout << "file string :" << endl;
    // for (StrBlob_ptr ch = fs_blob.begin(); ch != fs_blob.end(); ch.increase_ref())
    //     cout << ch.deref() << endl;

    while (1)
        ;

    return 0;
}