#include <forward_list>
#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

#include <functional>

#include <map>
#include <set>

using namespace std::placeholders;

template <typename T>
void print(T src)
{
    for (auto ch : src)
        cout << ch << ",";
    cout << endl;
}