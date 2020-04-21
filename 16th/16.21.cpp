// 16.21 实现自己的DebugDelete版本
#include <iostream>
#include <memory>

using namespace std;

class DebugDelete
{
private:
    std::ostream &dbgos;

public:
    DebugDelete(std::ostream &o = std::cout) : dbgos(o) {}
    template <typename T>
    void operator()(T *elem) const
    {
        dbgos << "delete by DebugDelete" << std::endl;
        delete elem;
    }
};

int main(int argc, const char **argv)
{
    DebugDelete d;
    int *a = new int;
    d(a);

    int *b = new int;
    DebugDelete()(b);

    {

        std::unique_ptr<int, DebugDelete> ui(new int, DebugDelete());
        // ui.release(); 释放ui但保留内存
        // ui.reset();   释放ui内存的东西,会调用DebugDelete
        std::cout << "/* message */" << std::endl;
    }
    while (1)
        ;
    return 0;
}