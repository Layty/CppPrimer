/*

定义  StrBlob类,数据成员是 vector<string> 的shared_ptr


*/

#include <vector>
#include <string>
#include <memory>
#include <initializer_list>

using namespace std;

class StrBlob
{
    using Blob_size_type = vector<string>::size_type;

private:
    /* data */
    shared_ptr<vector<string>> data;

public:
    StrBlob() : data(make_shared<vector<string>>()) {}
    StrBlob(initializer_list<string>li):(data(make_shared<vector<string>>(li)){}

    Blob_size_type size(){
        return data->size();
    }

    bool empty(){
        return data->empty();
    }

    void push_back(string& s){
        data->push_back(s);
    }
    void pop_back(){
        data->pop_back();
    }

    string& front(){
        return data->front();
    }

    string& back(){
        return data->back();
    }


     ~StrBlob();
};

StrBlob::StrBlob(/* args */)
{
}

StrBlob::~StrBlob()
{
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