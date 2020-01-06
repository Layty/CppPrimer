/*
编写程序，查找并删除forward_list中的奇数元素。
*/
#include <forward_list>
#include <iostream>
using namespace std;
int main(int argc, const char** argv)
{

    forward_list<int> flst = {2, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    auto prev = flst.before_begin();
    auto curr = flst.begin();

    while (curr != flst.end()) {
        if (*curr % 2) {
            curr = flst.erase_after(prev);
        }
        else {
            prev = curr;
            curr++;
        }
    }

    for (auto ch : flst) cout << ch << ",";

    while (1)
        ;
    return 0;
}