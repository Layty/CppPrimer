
#include <vector>
#include <string>
using namespace std;

int f()
{
    return 0;
}
int main(int argc, char const *argv[])
{
    string &&s1 = string();
    string &&s2 = string("123");
    // 虽然下面的编译器不会报错
    string("1") + string("2") = string("3");

    vector<int> vi(100);
    int &&r1 = f();
    int &r2 = vi[0];
    int &r3 = r1;
    int &&r4 = vi[0] * f();
    return 0;
}
