/*
12.26  使用 allocater 替代new
*/
#include <iostream>
#include <string>
#include <memory>
using namespace std;

void old_test()
{
    cout << "use new[] " << endl;
    string *const p = new string[10];
    string s, *q = p;
    while (cin >> s && q != p + 10)
    {
        *q++ = s; // q=s q++
    }
    const size_t size = q - p; // 实际使用的内存
    for (int i = 0; i < size; i++)
        cout << p[i] << endl;
    delete[] p;
    cout << "end of use new[] " << endl;
}

void new_test()
{
    cout << "use allocater " << endl;
    allocator<string> allocator_string;
    auto const p = allocator_string.allocate(10);
    string *q = p;

    string s;
    while (cin >> s && q != p + 10)
    {
        allocator_string.construct(q++, s);
    }
    for (size_t i = 0; i < q - p; i++)
    {
        cout << p[i] << endl;
    }
    while (q != p)
    {
        allocator_string.destroy(--q);
    }
    allocator_string.deallocate(p, 100);
    cout << "end of use allocater " << endl;
}

int main(int argc, char const *argv[])
{
    /* code */

    //old_test();

    new_test();
    while (1)
        ;

    return 0;
}
