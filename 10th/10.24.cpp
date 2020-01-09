#include "include.h"

bool check(int a, int sz)
{
    return a > sz;
}

int main(int argc, char const *argv[])
{
    vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    string s = "123";
    auto f = bind(check, _1, s.size());

    auto fst = find_if(v.begin(), v.end(), f);

    cout << *fst << endl;

    while (1)
        ;
    return 0;
}
