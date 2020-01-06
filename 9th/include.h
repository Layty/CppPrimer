#include <forward_list>
#include <iostream>
#include <list>
#include <vector>
#include <string>
using namespace std;

template <typename T> 
void print(T src)
{
    for (auto ch : src) 
        cout << ch <<",";
    cout<<endl;
}