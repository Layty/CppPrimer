// 17.1 定义一个保存三个 int 值的 tuple，并将其成员分别初始化为10、20和30。
// 17.2 定义一个 tuple，保存一个 string、一个vector 和一个 pair<string, int>。
#include <tuple>
#include <string>
#include <vector>

int main(int argc, const char **argv)
{
    std::tuple<int, int, int> a(10, 20, 30);
    std::tuple<std::string, std::vector<int>, std::pair<std::string, int>> b("hello", std::vector<int>({1, 2, 3}), std::make_pair<std::string, int>("123", 4));
    return 0;
}