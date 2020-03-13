/*

12.33 增加 QueryResult 的begin,end 取得set的begin,end  增加一个get_file  返回shared_ptr 指向QueryResult的文件也就是strBlob_ptr

12.32
重写TextQuery和QueryResult类，用StrBlob代替vector<vector>保存输入文件

TextQuery 使用StrBlob  存储shared_ptr<vector<string>>  文本
具体查询打印的时候,我们要从 *(StrBlob.ptr) 中取小标
也就是 使用 StrBlob_ptr 这个类指向了StrBlob中vector[下标]

github的答案是这里 使用 shared_ptr 执行StrBlob 也就是  shared_ptr<StrBlob> 的操作,
*/

/*
12.19 
12.20 读入文件 使用这个类
12.22 使用  const StrBlob类
			strBlob begin end 返回const
            底层指针是个const,只有在构造的时候赋值
            解引用的时候返回const  

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
#include <set>
#include <map>
#include <sstream>

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

    StrBlob_ptr begin() const; //{ return StrBlob_ptr(*this); }
    StrBlob_ptr end() const;   //{ return StrBlob_ptr(*this, data->size()); }

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
    StrBlob_ptr(const StrBlob &s, int offset = 0) : ptr(s.data), cur(offset) {}
    ~StrBlob_ptr() {}

    // * 解引用
    const string &deref() const;
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

const string &StrBlob_ptr::deref() const
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
StrBlob_ptr StrBlob::begin() const
{
    return StrBlob_ptr(*this);
}
StrBlob_ptr StrBlob::end() const
{
    return StrBlob_ptr(*this, data->size());
}

/******************************************************************************************************************/

class ResultQuery
{
    friend ostream &print(ostream &, const ResultQuery &);

public:
    // 单词
    string w;
    // 行号的列表
    shared_ptr<set<int>> lines;
    // 全部的文本,可以通过行号寻找
    StrBlob txtline; //----------modify

public:
    ResultQuery(string word, shared_ptr<set<int>> line_num, StrBlob txt) : w(word), lines(line_num), txtline(txt){}; //----------modify

    set<int>::iterator begin() const { return lines->begin(); } // 这里要使用const 因为下面的调用是使用  const ResultQuery&
    set<int>::iterator end() const { return lines->end(); }
    StrBlob get_file() { return txtline; }

    ~ResultQuery(){};
};

class TextQuery
{
private:
    /* data */
    StrBlob txtline; //----------modify
    // 因为在ret里面共享的是set的行号,所以这里也是行号共享指针,而不是整个map
    map<string, shared_ptr<set<int>>> data;

public:
    TextQuery(ifstream &file);
    ResultQuery Query(string &w);
    ~TextQuery(){};
};

TextQuery::TextQuery(ifstream &file) : txtline() //----------modify
{
    // 读入文件到文件流,保存每一行到vector<string>
    string s;
    int line_at = 0;
    while (getline(file, s))
    {
        txtline.push_back(s); //----------modify
        string ch;
        istringstream ss(s);
        while (ss >> ch)
        {
            if (!data[ch])
                data[ch].reset(new set<int>);
            data[ch]->insert(line_at);
        }
        line_at++;
    }
}

ResultQuery TextQuery::Query(string &w)
{
    static shared_ptr<std::set<int>> nodate(new std::set<int>);
    auto found = data.find(w);
    if (found == data.end())
        return ResultQuery(w, nodate, txtline);
    else
        return ResultQuery(w, data[w], txtline);
}
//ostream &print(ostream &, const ResultQuery &)
ostream &print(ostream &out, const ResultQuery &want)
{
    out << "----------------------------------------------" << endl;
    out << "string:" << want.w << endl;
    out << "Txt List:" << endl;

    for (auto it = want.begin(); it != want.end(); it++)
    {
        StrBlob_ptr xx(want.txtline, *it);             //----------modify
        out << *it << ":\t\t\t" << xx.deref() << endl; //----------modify
    }

    //for(auto it=want.begin();)
    //if (want.lines) // 先要判断指针是否存在
    {
        // for (auto ls : *(want.lines))
        // {
        //     StrBlob_ptr xx(want.txtline, ls);             //----------modify
        //     out << ls << ":\t\t\t" << xx.deref() << endl; //----------modify
        // }

        //qr.input->at(i)
    }

    out << "----------------------------------------------" << endl;
    return out;
}

void runQueries(ifstream &file)
{
    // 从文件流建立查询的数据
    TextQuery tq(file);
    while (true)
    {
        cout << "Enter what you want to find?" << endl;
        string s;
        if (!(cin >> s) || s == "q")
            break;
        print(cout, tq.Query(s)) << endl;
    }
}

int main(int argc, char const *argv[])
{
    ifstream fs("D:\\a.txt");
    if (fs)
        runQueries(fs);
    else
        cout << "fs open failed " << endl;

    while (1)
        ;
    return 0;
}
