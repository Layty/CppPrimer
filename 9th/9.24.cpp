#include <iostream>
#include <vector>
using namespace std;

int main(int argc, const char** argv)
{

    std::vector<int> v;
    std::cout << v.at(0);    // terminating with uncaught exception of type std::out_of_range
    std::cout << v[0];       // Segmentation fault: 11
    std::cout << v.front();  // Segmentation fault: 11
    std::cout << *v.begin(); // Segmentation fault: 11

    while (1) return 0;
}
