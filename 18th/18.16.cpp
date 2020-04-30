//假定在下面的代码中标记为“位置1”的地方是对命名空间 Exercise中所有成员的using声明，请解释代码的含义。
// 如果这些using声明出现在“位置2”又会怎样呢？将using声明变为using指示，重新回答之前的问题。
//

#include <iostream>
using namespace std;
namespace Exercise
{
    int ivar = 0;
    double dvar = 0;
    const int limit = 1000;
} // namespace Exercise
int ivar = 0;
//位置1
// using Exercise::dvar;
// using Exercise::ivar; //1..编译不过去
// using Exercise::limit;
//  using namespace Exercise;

int main(int argc, char const *argv[])
{
    //位置2 编译不过去
    // using Exercise::dvar;
    // using Exercise::ivar;
    // using Exercise::limit;
    //using namespace Exercise;

    double dvar = 3.1416;
    int iobj = limit + 1;
    ++ivar;
    ++::ivar;

    std::cout << "ivar= " << ivar << std::endl;
    std::cout << "::ivar= " << ::ivar << std::endl;
    std::cout << "iobj= " << iobj << std::endl;
    while (1)
        ;
    return 0;
}
