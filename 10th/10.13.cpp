
/*
标准库定义了名为partition的算法，它接受一个谓词，对容器内容进行划分，使得谓词为true的值对排在容器的前半部分，而使谓词为false的值会排在后半部分。
算法返回一个迭代器，指向最后一个使谓词为true的元素之后的位置。编写函数，接受一个string，返回一个bool值，指出string是否有5个或更多字符。
使用此函数划分words。打印出长度大于等于5的元素
*/
#include "include.h"

bool bigThen5(const string &a)
{
    return a.size() > 5;
}

int main(int argc, char const *argv[])
{
    vector<string> v = {"123456",
                        "12345",
                        "111222",
                        "55555555"};

    auto last_true = partition(v.begin(), v.end(), bigThen5);

    for (auto i = v.begin(); i != last_true; i++)
    {
        cout << *i << endl;
    }

    while (1)
        ;
    return 0;
}
