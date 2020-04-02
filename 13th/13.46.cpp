
#include <vector>
using namespace std;

int f()
{
    return 0;
}
int main(int argc, char const *argv[])
{
    vector<int> vi(100);
    int &&r1 = f();
    int &r2 = vi[0];
    int &r3 = r1;
    int &&r4 = vi[0] * f();
    return 0;
}
