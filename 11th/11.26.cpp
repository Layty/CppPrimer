/*可以用什么类型来对一个map进行下标操作？
下标运算符返回的类型是什么？请给出一个具体例子 -- 
即，定义一个map，然后写出一个可以用来对map进行下标操作的类型以及下标运算符会返回的类型*/

#include "../include/include.h"

int main(int argc, char const *argv[])
{
    map<int, int> m;

    //map<int, int>::iterator in = m.begin();
    m[0] = 1;
    map<int, int>::mapped_type elem = m[0];
    cout << elem << endl;

    // 不懂
    //type to subscript: St3mapIiiSt4lessIiESaISt4pairIKiiEEE
    //returned from the subscript operator: i
    std::cout << "type to subscript: " << typeid(m).name() << std::endl;
    std::cout << "returned from the subscript operator: " << typeid(decltype(m[0])).name() << std::endl;

    while (1)
        ;
    return 0;
}
