// 12.2 编写你自己的StrBlob类，包含const版本的front和back

#include "../include/include.h"
#include <initializer_list>
#include <memory>
#include <exception>
class StrBlob
{

public:
    typedef vector<string>::size_type size_type;
    StrBlob() : data(make_shared<vector<string>>()) {}
    StrBlob(initializer_list<string> li) : data(make_shared<vector<string>>(li)) {}
    size_type size() const
    {
        return data->size();
    }
    bool empty() const
    {
        return data->empty();
    }

    void push_back(const string &s)
    {
        data->push_back(s);
    }
    void pop_back();

    string &front();
    string &back();
    const string &front() const;
    const string &back() const;

    ~StrBlob();

private:
    shared_ptr<vector<string>> data;
    void check(size_type i, const string &message) const
    {
        if (i >= data->size())
            throw std::out_of_range(message);
    }
};

StrBlob::~StrBlob()
{
}

string &StrBlob::front()
{
    check(0, "front on empty StrBlob");
    return data->front();
}
string &StrBlob::back()
{
    check(0, "back on empty StrBlob");
    return data->back();
}
const string &StrBlob::front() const
{
    check(0, "front on empty StrBlob");
    return data->front();
}
const string &StrBlob::back() const
{
    check(0, "back on empty StrBlob");
    return data->back();
}

void StrBlob::pop_back()
{
    check(0, "pop_back on empty StrBlob");
    data->pop_back();
}

int main(int argc, const char **argv)
{

    StrBlob csb{"1", "2", "3"};
    StrBlob sb{"A1", "A2", "A3"};

    std::cout << csb.front() << " " << csb.back() << std::endl;
    sb.back() = "change";
    std::cout << sb.front() << " " << sb.back() << std::endl;
    while (1)
        ;
    return 0;
}