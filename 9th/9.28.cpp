/*
编写函数，接受一个forward_list和两个string共三个参数。
函数应在链表中查找第一个string，并将第二个string插入到紧接着第一个string之后的位置。
若第一个string未在链表中，则将第二个string插入到链表末尾。
*/

#include <forward_list>
#include <iostream>
#include <string>
using namespace std;

void insert_lst(forward_list<string>& src, string after, string what)
{
    if (src.empty()) {
        return;
    }

    auto prev = src.before_begin();
    auto curr = src.begin();

    while (curr != src.end()) {
        if (*curr == after) {
            src.insert_after(curr, what);
            return;
        }
        else {
            curr++;
            prev++;
        }
    }
    src.insert_after(prev, what);
}

int main(int argc, const char** argv)
{

    forward_list<string> lst = {"www", ".baidu", ".com"};

    insert_lst(lst, ".baidu", ".hello");
    for (auto ch : lst) cout << ch << endl;
    insert_lst(lst, "xxx", ".hello");
    for (auto ch : lst) cout << ch << endl;
    while (1)
        ;
    return 0;
}